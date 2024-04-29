/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 20:43:12 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/28 17:08:12 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	try_fork(t_philo *philo)
{
	while (!lock_fork(philo))
		if (check_dead(philo))
			return (1);
	print_msg(philo->num, FORK, philo->config);
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (philo->num % 2)
		if (try_fork(philo->prev))
			return (1);
	if (try_fork(philo))
		return (2);
	if (!(philo->num % 2))
		if (try_fork(philo->prev))
			return (3);
	return (0);
}

int	drop_forks(t_philo *philo)
{
	if (philo->num % 2)
		unlock_fork(philo->prev);
	unlock_fork(philo);
	if (!(philo->num % 2))
		unlock_fork(philo->prev);
	return (check_dead(philo));
}

int	philo_eat(t_philo *philo, int *loop)
{
	philo->tm_alive = get_time();
	print_msg(philo->num, EAT, philo->config);
	++(*loop);
	if ((*loop) == philo->config->num_loops)
		add_eat(philo);
	while (get_time() - philo->tm_alive < philo->config->time_eat &&\
		!check_flags(philo->config))
	{
		if (check_dead(philo))
			return (-1);
		usleep(420);
	}
	return (check_dead(philo));
}

int	philo_sleep(t_philo *philo)
{
	print_msg(philo->num, SLEEP, philo->config);
	while (get_time() - philo->tm_alive < philo->config->time_sleep &&\
		!check_flags(philo->config))
	{
		if (check_dead(philo))
			return (-1);
		usleep(420);
	}
	return (check_dead(philo));
}
