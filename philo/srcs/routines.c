/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 00:56:03 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/30 18:42:36 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	take_forks(t_philo *philo)
{
	while (!change_value(philo->fork_left, true))
	{
		time_sleep(100);
		if (check_dead(philo))
			return (false);
	}
	print_msg(philo->dead_flag, "take left fork", philo);
	while (!change_value(philo->fork_right, true))
	{
		time_sleep(100);
		if (check_dead(philo))
			return (false);
	}
	print_msg(philo->dead_flag, "take right fork", philo);
	return (true);
}

bool	drop_forks(t_philo *philo)
{
	while (change_value(philo->fork_left, false))
	{
		if (check_dead(philo))
			return (false);
		time_sleep(100);
	}
	while (change_value(philo->fork_right, false))
	{
		if (check_dead(philo))
			return (false);
		time_sleep(100);
	}
	return (true);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->time_alive = now();
	while (!philo->dead_flag->value)
	{
		//printf("Soy philo %i\n", philo->num);
		if (!take_forks(philo))
			return (NULL);
		//if (!take_forks(philo))
		//	return ((void *)change_value(philo->dead_flag, true));
		//	return (NULL);
	}
	return (NULL);
}
