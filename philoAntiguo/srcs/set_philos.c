/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:50:33 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/28 21:23:05 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*list_union(t_philo *first, t_philo *last)
{
	if (!first)
		return (last);
	while (first->prev)
		first = first->prev;
	last->next = first;
	first->prev = last;
	return (first);
}

t_philo	*set_philos(t_config *config, int start_philo)
{
	t_philo	*aux;
	t_philo	*res;

	aux = 0;
	while (start_philo <= config->num_philos)
	{
		res = aux;
		aux = ft_calloc(sizeof(t_philo), 1);
		if (!aux)
			return (NULL);
		if (pthread_mutex_init(&aux->fork, NULL))
			return (NULL);
		aux->num = start_philo;
		aux->config = config;
		aux->prev = res;
		if (res)
			res->next = aux;
		++start_philo;
	}
	return (list_union(res, aux));
}

static void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		loop;

	philo = (t_philo *)arg;
	loop = 0;
	philo->tm_alive = get_time();
	while (!check_flags(philo->config))
	{
		if (take_forks(philo))
			return (NULL);
		if (philo_eat(philo, &loop))
			return (NULL);
		drop_forks(philo);
		if (philo_sleep(philo))
			return (NULL);
		print_msg(philo->num, THINK, philo->config);
	}
	return (NULL);
}

int	start_routines(t_philo *philos, t_config *config)
{
	int	num_philos;

	num_philos = config->num_philos;
	while (num_philos--)
	{
		if (pthread_create(&philos->philo, NULL, philo_routine, philos))
			return (-1);
		philos = philos->next;
	}
	return (0);
}

int	wait_philos(t_philo *philos, t_config *config)
{
	int	num_philos;
	
	num_philos = config->num_philos;
	while (num_philos--)
	{
		if (pthread_join(philos->philo, NULL))
			return (-1);
		philos = philos->next;
	}
	printf("PHILO %i FINISH", philos->num);
	return (0);
}
