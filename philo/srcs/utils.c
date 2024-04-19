/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:12:36 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/19 18:29:03 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_config	*get_config(char **argv)
{
	t_config	*res;

	res = ft_calloc(sizeof(t_config), 1);
	if (!res)
		return (0);
	res->num_philos = ft_atoli(argv[1]);
	res->time_die = ft_atoli(argv[2]);
	res->time_eat = ft_atoli(argv[3]);
	res->time_sleep = ft_atoli(argv[4]);
	res->start_time = get_time();
	return (res);
}

long int	get_time(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return ((long int)start.tv_sec * 1000);
}

void	message(t_philo *philo, pthread_mutex_t *stop, int flag, char *msg)
{
	long int	time_ms;

	pthread_mutex_lock(stop);
	time_ms = get_time() - philo->config->start_time;
	printf("%lims %i is %s", time_ms, philo->num, msg);
	philo->flags ^= flag;
	pthread_mutex_unlock(stop);
}

void	print_msg(t_philo *philos)
{
	pthread_mutex_t	stop;

	pthread_mutex_init(&stop, NULL);
	if (philos->num)
	{
		if (philos->flags & EAT)
			message(philos, &stop, EAT, "eating\n");
		else if (philos->flags & SLEEP)
			message(philos, &stop, SLEEP, "sleeping\n");
		else if (philos->flags & THINK)
			message(philos, &stop, THINK, "thinking\n");
		else if (philos->flags & DEAD)
			message(philos, &stop, DEAD, "dead\n");
	}
}
