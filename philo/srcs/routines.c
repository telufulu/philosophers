/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 00:56:03 by telufulu          #+#    #+#             */
/*   Updated: 2024/05/03 21:23:21 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	take_forks(t_philo *philo)
{
	check_dead(philo);
	if (!change_value(philo->fork_left, true))
	{
		print_msg(philo->dead_flag, "\033[0;95mthinking", philo);
		while (!change_value(philo->fork_left, true))
		{
			if (check_dead(philo))
				return (false);
			time_sleep(philo->delay);
		}
	}
	print_msg(philo->dead_flag, "\033[0;96mtake left fork", philo);
	while (!change_value(philo->fork_right, true))
	{
		if (check_dead(philo))
			return (false);
		time_sleep(philo->delay);
	}
	print_msg(philo->dead_flag, "\033[0;94mtake right fork", philo);
	return (true);
}

bool	drop_forks(t_philo *philo)
{
	change_value(philo->fork_left, false);
	change_value(philo->fork_right, false);
	return (false);
}

bool	philo_eat(t_philo *philo)
{
	philo->time_alive = now();
	--philo->my_loops;
	if (!philo->my_loops)
		--(*philo->num_loops);
	print_msg(philo->dead_flag, "\033[0;92meating", philo);
	if (now() - philo->time_alive + philo->time_eat > philo->time_die)
	{
		time_sleep(philo->time_die - (now() - philo->time_alive));
		return (false);
	}
	else
		time_sleep(philo->time_eat);
	return (true);
}

bool	philo_sleep(t_philo *philo)
{
	print_msg(philo->dead_flag, "\033[0;93msleeping", philo);
	if (now() - philo->time_alive + philo->time_sleep > philo->time_die)
	{
		time_sleep(philo->time_die - (now() - philo->time_alive));
		check_dead(philo);
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
	if (philo->num % 2)
		time_sleep(philo->delay);
	while (!one_is_dead(philo->dead_flag) && !no_loops(philo))
	{
		if (!take_forks(philo))
			return (NULL);
		if (!philo_eat(philo) || one_is_dead(philo->dead_flag))
			return (check_dead(philo), NULL);
		if (drop_forks(philo) || one_is_dead(philo->dead_flag))
			return (NULL);
		if (!philo_sleep(philo) || one_is_dead(philo->dead_flag))
			return (NULL);
	}
	return (NULL);
}
