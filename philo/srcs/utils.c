/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:09:19 by telufulu          #+#    #+#             */
/*   Updated: 2024/05/03 18:00:31 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Returns time since January 1 1970 in miliseconds
uint64_t	now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

// Make a thread or a process msecs miliseconds
void	time_sleep(uint64_t msecs)
{
	uint64_t	diff;

	diff = now() + msecs;
	while (diff > now())
		usleep(200);
}

// Frees a mutex_value structure
void	free_mutex(t_mutex_value *mutex)
{
	if (mutex)
	{
		pthread_mutex_destroy(&mutex->mutex);
		free(mutex);
		mutex = NULL;
	}
}

// It detaches de threads and frees all the resources allocated with malloc.
void	free_all(t_mutex_value *dead, t_philo **philos)
{
	t_philo	**aux;

	aux = philos;
	free_mutex(dead);
	while (aux && *aux)
	{
		free_mutex((*aux)->fork_left);
		free((*aux));
		*aux = NULL;
		++aux;
	}
	free(philos);
	philos = NULL;
}

// Choose the minimum number between time_die, time_sleep, time_eat, and use it
// for sleep threads. The result number is the (smaller / 100)ms
uint64_t	set_delay(size_t *args)
{
	size_t	res;
	int		i;

	res = UINT_MAX;
	i = 0;
	while (++i < 4)
		if (args[i] < res)
			res = args[i];
	if (!res)
		res = 1000;
	return (res / 100);
}
