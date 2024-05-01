/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 00:56:03 by telufulu          #+#    #+#             */
/*   Updated: 2024/05/01 22:42:36 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	take_forks(t_philo *philo)
{
	while (!change_value(philo->fork_left, true))
	{
		if (check_dead(philo))
			return (false);
		time_sleep(10);
	}
	print_msg(philo->dead_flag, "take left fork", philo);
	while (!change_value(philo->fork_right, true))
	{
		if (check_dead(philo))
			return (false);
		time_sleep(10);
	}
	print_msg(philo->dead_flag, "take right fork", philo);
	return (true);
}

bool	drop_forks(t_philo *philo)
{
	while (change_value(philo->fork_left, false))
		if (check_dead(philo))
			return (false);
	while (change_value(philo->fork_right, false))
		if (check_dead(philo))
			return (false);
	return (true);
}

bool	philo_eat(t_philo *philo)
{
	philo->time_alive = now();
	print_msg(philo->dead_flag, "eating", philo);
	if (now() - philo->time_alive > philo->time_eat)
	{
		time_sleep(now() - philo->time_alive);
		return (false);
	}
	else
		time_sleep(philo->time_eat);
	return (true);
}

bool	philo_sleep(t_philo *philo)
{
	print_msg(philo->dead_flag, "sleeping", philo);
	if (now() - philo->time_alive > philo->time_sleep)
	{
		time_sleep(now() - philo->time_alive);
		return (false);
	}
	else
		time_sleep(philo->time_sleep);
	return (true);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->time_alive = now();
	while (!is_dead(philo))
	{
		if (!take_forks(philo))
			return (NULL);
		if (!philo_eat(philo))
			return (NULL);
		if (!drop_forks(philo))
			return (NULL);
		if (!philo_sleep(philo))
			return (NULL);
		print_msg(philo->dead_flag, "thinking", philo);
	}
	return (NULL);
}
