/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:12:36 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/18 20:14:40 by telufulu         ###   ########.fr       */
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

void	*print_msg(void *arg)
{
	t_philo		*philos;
	long int	time;

	philos = (t_philo *)arg;
	time = philos->config->start_time;
	while (!philos->config->dead_flag)
	{
		if (philos->flags & THINK)
		{
			philos->flags ^= THINK;
			printf("%zums %i is thinking\n", get_time() - time, philos->num);
		}
		if (philos->flags & EAT)
		{
			philos->flags ^= EAT;
			printf("%zums %i is eating\n", get_time() - time, philos->num);
		}
		if (philos->flags & SLEEP)
		{
			philos->flags ^= SLEEP;
			printf("%zums %i is sleeping\n", get_time() - time, philos->num);
		}
		if (philos->flags & DEAD)
		{
			philos->config->dead_flag = 1;
			printf("%zums %i is dead\n", get_time() - time, philos->num);
		}
		philos = philos->next;
	}
	return (0);
}
