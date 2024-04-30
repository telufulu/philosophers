/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 20:42:10 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/28 16:58:10 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	add_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->config->stop);
	++philo->config->num_eats;
	pthread_mutex_unlock(&philo->config->stop);
}

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->config->stop);
	if (get_time() - philo->tm_alive >= philo->config->time_die)
	{
		pthread_mutex_unlock(&philo->config->stop);
		return (print_msg(philo->num, DEAD, philo->config));
	}
	pthread_mutex_unlock(&philo->config->stop);
	return (0);
}

int lock_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	if (!philo->fork_flag)
	{
		philo->fork_flag = 1;
		pthread_mutex_unlock(&philo->fork);
		return (0);
	}
	pthread_mutex_unlock(&philo->fork);
	return (1);
}

void unlock_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	if (philo->fork_flag)
		philo->fork_flag = 0;
	pthread_mutex_unlock(&philo->fork);
}