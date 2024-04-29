/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:09:19 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/29 01:54:22 by telufulu         ###   ########.fr       */
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

// Creates and initialize a new mutex. If some problem happens, returns NULL,
//otherwise, returns the new mutex.
t_mutex_value	*new_mutex(void)
{
	t_mutex_value	*res;

	res = ft_calloc(sizeof(t_mutex_value), 1);
	if (!res)
		return (NULL);
	res->value = false;
	if (pthread_mutex_init(&res->mutex, NULL))
		return (NULL);
	return (res);
}

// Create a new philosopher, and initialize everythin but the philo thread. 
//If some error happens, it returns NULL.
t_philo	new_philo(t_mutex_value *dead_flag, size_t *args, int num)
{
	t_philo	philo;

	philo.fork_left = (t_mutex_value *)new_mutex();
	philo.dead_flag = dead_flag;
	philo.num_philos = args[0];
	philo.time_die = args[1];
	philo.time_eat = args[2];
	philo.time_sleep = args[3];
	philo.num_loops = args[4];
	if (!philo.num_loops)
		philo.num_loops = -1;
	philo.num = num;
	return (philo);
}

// Initializes the threads from the philosophers and assing right forks.
//If something failes, returns 1, otherwise, returns 0.
int	init_threads(t_philo *philo, int num_threads)
{
	int	i;

	i = 0;
	while (i < num_threads)
	{
		if (i + 1 == num_threads)
		{
			philo[i].fork_right = philo[i].fork_left;
			philo[i].fork_left = philo[0].fork_left;
		}
		else
			philo[i].fork_right = philo[i + 1].fork_left;
		if (pthread_create(&philo[i].philo, NULL, philo_routine, philo + i))
			return (1);
		++i;
	}
	return (0);
}

// Gets main arguments, check them and assign them to an array.
// If some of the numbers are not uint64_t, it returns 0.
int	get_args(char **argv, size_t *args)
{
	args[0] = ft_atolui(argv[0]);
	args[1] = ft_atolui(argv[1]);
	args[2] = ft_atolui(argv[2]);
	args[3] = ft_atolui(argv[3]);
	if (argv[4])
		args[4] = ft_atolui(argv[4]);
	else
		args[4] = -1;
	return (0);
}

// Returns an array of philos. If some error happens, ir returns NULL
t_philo	*init_philos(t_mutex_value *dead_flag, size_t *args)
{
	size_t	num;
	t_philo *res;

	num = 0;
	res = ft_calloc(sizeof(t_philo), args[0]);
	if (!res)
		return (NULL);
	while (num < args[0])
	{
		res[num] = new_philo(dead_flag, args, num + 1);
		++num;
	}
	return (res);
}

// FALTA DESCRIPCIÓN
bool wait_philos(t_philo *philos)
{
	size_t i;

	i = 0;
	while (i < philos->num_philos - 1)
	{
		if (pthread_join(philos[i].philo, NULL))
			return (false);
		++i;
		return (change_value(philos[i].dead_flag, true));
	}
	return (false);
}

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
