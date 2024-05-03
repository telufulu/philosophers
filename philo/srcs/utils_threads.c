/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:09:19 by telufulu          #+#    #+#             */
/*   Updated: 2024/05/03 17:59:51 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Used, for example, to take forks. If it can change the value, it returns
// true, otherwise, returns false.
bool	change_value(t_mutex_value *mutex, bool new_value)
{
	pthread_mutex_lock(&mutex->mutex);
	if (mutex->value != new_value)
	{
		mutex->value = new_value;
		pthread_mutex_unlock(&mutex->mutex);
		return (true);
	}
	pthread_mutex_unlock(&mutex->mutex);
	return (false);
}

// FALTA DESCRIPCIÓN
bool	wait_philos(t_philo **philos)
{
	size_t	i;

	i = 0;
	while (i < philos[i]->num_philos - 1)
	{
		if (pthread_join(philos[i]->philo, NULL))
			return (false);
		++i;
	}
	i = 0;
	while (i < philos[i]->num_philos - 1)
		pthread_detach(philos[i++]->philo);
	return (true);
}

// FALTA DESCRIPCIÓN
bool	one_is_dead(t_mutex_value *dead)
{
	pthread_mutex_lock(&dead->mutex);
	if (dead->value)
	{
		pthread_mutex_unlock(&dead->mutex);
		return (true);
	}
	pthread_mutex_unlock(&dead->mutex);
	return (false);
}

// Checks if the philo is dead. If it's dead, 
// changes the dead_flag and returns true
bool	check_dead(t_philo *philo)
{
	if (one_is_dead(philo->dead_flag))
		return (true);
	if (now() - philo->time_alive >= philo->time_die)
	{
		change_value(philo->dead_flag, true);
		print_msg(philo->dead_flag, "\033[1;31mis dead", philo);
		return (true);
	}
	return (false);
}

// Prints state messages from philos in a protective way
void	print_msg(t_mutex_value *stop, char *msg, t_philo *philo)
{
	pthread_mutex_lock(&stop->mutex);
	printf("%lums philo %i %s\033[0m\n", now() - philo->start_time, \
		philo->num, msg);
	pthread_mutex_unlock(&stop->mutex);
}
