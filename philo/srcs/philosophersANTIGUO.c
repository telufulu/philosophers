/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:45:52 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/11 17:42:16 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_time(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return (start.tv_sec * 1000 + start.tv_sec);
}

t_config	*get_config(char **argv)
{
	t_config	res;

	res = ft_calloc(sizeof(t_config), 1);
	if (!res)
		return (NULL);
	res->time_die = (float)ft_atoi(arg[2]);
	res->time_eat = (float)ft_atoi(arg[3]);
	res->time_sleep = (float)ft_atoi(arg[4]);
	res->time = get_time();
	return (res);
}

void	*philo_routine(void **arg)
{
	t_philo	*aux;
	
	aux = *(t_philo *)arg;
	while (!*aux->dead_flag)
	{
	}
	return (0);
}

t_philo	*new_thread(t_philo *philo, t_config *config, int num)
{
	t_philo	*aux;

	aux = ft_calloc(sizeof(t_philo), 1);
	if (!aux)
		return (NULL);
	aux->prev = philo;
	aux->num_philo = num;
	aux->config = config;
	pthread_create(&aux->philo, NULL, philo_routine, argv);
	return (aux);
}

void	create_philos(t_philo **first, t_config *config, int num_of_philos)
{
	t_philo	*aux;
	int		i;

	i = 0;
	(*first) = new_thread(NULL, argv, ++i);
	aux = (*first);
	while (i <= num_of_philos)
	{
		aux->next = new_thread(aux, argv, i);
		aux = aux->next;
		++i;
	}
	(*first)->prev = aux;
	aux->next = (*first);
}

void	*print_status(t_philo *philos)
{
	while (!(philos->flags & DEAD))
	{
		if (philos->flags & FORK)
			printf("%i has taken a fork\n", philos->num_philo);
		if (philos->flags & EAT)
			printf("%i is eating\n", philos->num_philo);
		if (philos->flags & SLEEP)
			printf("%i is sleaping\n", philos->num_philo);
		if (philos->flags & THINK)
			printf("%i is thinking\n", philos->num_philo);
		philos = philos->next;
	}
	if (philos->flags & DEAD)
		printf("%i is dead\n", philos->num_philo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo		*philosophers;
	t_config	*config;
	pthread_t	msg;

	philosophers = NULL;
	if (argc == 5 || argc == 6)
	{
		config = get_config(argv);
		if (!config)
			return (ft_error("config failed\n"));
		create_philos(&philosophers, config, ft_atoi(argv[1]));
		if (!philosophers || !philosophers->prev)
			return (ft_error("Fallo al crear hilo"));
		print_status(philosophers);
	}
	else
		return (ft_error(argv[1]));
	return (0);
}
