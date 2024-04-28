/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:12:36 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/28 19:47:23 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	get_time(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return ((long int)start.tv_sec * 1000 + start.tv_usec / 1000);
}

int	get_config(t_config *config, char **argv)
{
	config->dead_flag = 0;
	config->num_eats = 0;
	config->num_philos = ft_atolui(argv[0]);
	config->time_die = ft_atolui(argv[1]);
	config->time_eat = ft_atolui(argv[2]);
	config->time_sleep = ft_atolui(argv[3]) + config->time_eat;
	config->start_time = get_time();
	if (argv[4])
		config->num_loops = ft_atolui(argv[4]);
	else
		config->num_loops = -1;
	if (pthread_mutex_init(&config->stop, NULL))
		return (-1);
	if (!config->num_philos || !config->time_die ||\
		!config->time_eat || !config->time_sleep ||\
		(argv[4] && !config->num_loops))
		return (-1);
	return (0);
}

int	check_flags(t_config *config)
{
	pthread_mutex_lock(&config->stop);
	if (config->dead_flag > 0|| config->num_eats == config->num_philos)
	{
		pthread_mutex_unlock(&config->stop);
		return (1);
	}
	pthread_mutex_unlock(&config->stop);
	return (0);
}

int	print_msg(int philo, int flag, t_config *config)
{
	int	time;

	pthread_mutex_lock(&config->stop);
	time = get_time() - config->start_time;
	if (!config->dead_flag)
	{
		if (flag == DEAD)
		{
			++config->dead_flag;
			printf("%ims\tPhilo %i is dead\n", time, philo);
			pthread_mutex_unlock(&config->stop);
			return (1);
		}
		else if (flag == FORK)
			printf("%ims\tPhilo %i has taken a fork\n", time, philo);
		else if (flag == EAT)
			printf("%ims\tPhilo %i is eating\n", time, philo);
		else if (flag == SLEEP)
			printf("%ims\tPhilo %i is sleeping\n", time, philo);
		else if (flag == THINK)
			printf("%ims\tPhilo %i is thinking\n", time, philo);
	}
	pthread_mutex_unlock(&config->stop);
	return (0);
}
