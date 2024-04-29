#include "philo.h"
#include <string.h>

uint64_t	now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	time_sleep(uint64_t msecs)//, t_philo *philo)
{
	uint64_t	diff;

	diff = now() + msecs;
	while (diff > now())// && !philo->diners_exit)
		usleep(200);
}

void secured_print(const char *message, t_philo *philo)
{
	if (philo->someone_dead->value)
		return ;
	pthread_mutex_lock(philo->print_mutex);
	printf("%llums philo %i is %s\n", now() - philo->start_time, philo->num, message);
	pthread_mutex_unlock(philo->print_mutex);
}

t_secured_value *new_sec_value()
{
	t_secured_value *sec_value;

	sec_value = ft_calloc(1, sizeof(t_secured_value));
	pthread_mutex_init(&sec_value->mutex, NULL);
	return (sec_value);
}

t_config *new_config(char **argv)
{
	t_config *config;

	config = ft_calloc(1, sizeof(t_config));
	config->num_philos = ft_atolui(argv[0]);
	config->die_time = ft_atolui(argv[1]);
	config->eat_time = ft_atolui(argv[2]);
	config->sleep_time = ft_atolui(argv[3]);
	config->start_time = now();
	pthread_mutex_init(&config->print_mutex, NULL);
	config->someone_dead = new_sec_value();
	if (argv[4])
		config->loop_times = ft_atolui(argv[4]);
	else
		config->loop_times = -1;
	return (config);
}

t_philo new_philo(t_config *config, int num)
{
	t_philo philo;

	philo.num = num;
	philo.eat_time = config->eat_time;
	philo.die_time = config->die_time;
	philo.sleep_time = config->sleep_time;
	philo.start_time = config->start_time;
	philo.alive_time = now() + philo.die_time;
	philo.loop_times = config->loop_times;
	philo.fork_left = new_sec_value();
	philo.print_mutex = &config->print_mutex;
	philo.someone_dead = config->someone_dead;
	return (philo);
}

bool philo(t_config *config)
{
	size_t i;

	config->philos = malloc(sizeof(t_philo) * config->num_philos);
	if (!config->philos)
		return (false);
	i = 0;
	while (i < config->num_philos)
	{
		config->philos[i] = new_philo(config, i + 1);
		++i;
	}
	i = 0;
	while (i < config->num_philos)
	{
		if (i == config->num_philos - 1)
		{
			config->philos[i].fork_right = config->philos[i].fork_left;
			config->philos[i].fork_left = config->philos[0].fork_left;
		}
		else
			config->philos[i].fork_right = config->philos[i + 1].fork_left;
		++i;
	}
	return (true);
}

bool set_secured_value(t_secured_value *sec_value, bool value)
{
	pthread_mutex_lock(&sec_value->mutex);
	if (sec_value->value != value)
	{
		sec_value->value = value;
		pthread_mutex_unlock(&sec_value->mutex);
		return (true);
	}
	pthread_mutex_unlock(&sec_value->mutex);
	return (false);
}

bool take_fork(t_secured_value *sec_value)
{
	return (set_secured_value(sec_value, true));
}

bool drop_fork(t_secured_value *sec_value)
{
	return (set_secured_value(sec_value, false));
}

bool philo_eat(t_philo *philo)
{
	bool left;
	bool right;
	uint64_t alive_time;

	philo->alive_time = now() + philo->die_time;
	alive_time = philo->alive_time - now();
	while (philo->alive_time > now())
	{
		left = take_fork(philo->fork_left);
		right = take_fork(philo->fork_right);
		if (left & right)
		{
			secured_print("tenedor izq...", philo);
			secured_print("tenedor der...", philo);
			secured_print("comiendo...", philo);
			if (alive_time < philo->eat_time)
			{
				time_sleep(alive_time);
				return (false);
			}
			time_sleep(philo->eat_time);
			drop_fork(philo->fork_left);
			drop_fork(philo->fork_right);
			philo->loop_times -= (philo->loop_times > 0);
			return (true);
		}
		if (left)
			drop_fork(philo->fork_left);
		else if (right)
			drop_fork(philo->fork_right);
	}
	return (false);
}

bool philo_sleep(t_philo *philo)
{
	uint64_t alive_time;

	secured_print("durmiendo...", philo);
	alive_time = philo->alive_time - now();
	if (alive_time < philo->sleep_time)
	{
		time_sleep(alive_time);
		return (false);
	}
	time_sleep(philo->sleep_time);
	return (true);
}


void *philo_routine(void *content)
{
	t_philo *philo;

	philo = content;
	secured_print("iniciado", philo);
	while (!philo->someone_dead->value)
	{
		if (!philo_eat(philo) || !philo_sleep(philo))
		{
			secured_print("ha muerto...\n", philo);
			set_secured_value(philo->someone_dead, true);
			break ;
		}
	}
	return NULL;
}

void start_threads(t_config *config)
{
	size_t i;

	i = 0;
	while (i < config->num_philos)
	{
		usleep(50);
		pthread_create(&config->philos[i].pid, NULL, philo_routine, config->philos + i);
		++i;
	}

}

bool wait_threads(t_config *config)
{
	size_t i;

	i = 0;
	while (i < config->num_philos)
	{
		if (pthread_join(config->philos[i].pid, NULL))
		{
			printf("join ha fallado\n");
			return (false);
		}
		++i;
	}
	return (true);
}

int main(int argc, char **argv)
{
	t_config *config;

	if (argc < 5 && argc > 6)
		return ft_error("Wrong arguments"); 
	config = new_config(argv +1);
	philo(config);
	start_threads(config);
	if (!wait_threads(config))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
