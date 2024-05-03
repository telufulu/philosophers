/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:09:19 by telufulu          #+#    #+#             */
/*   Updated: 2024/05/03 18:00:15 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	{
		free(res);
		res = NULL;
		return (NULL);
	}
	return (res);
}

// Create a new philosopher, and initialize everythin but the philo thread. 
//If some error happens, it returns NULL.
t_philo	*new_philo(t_mutex_value *dead_flag, size_t *args, int num)
{
	t_philo	*philo;

	philo = ft_calloc(sizeof(t_philo), 1);
	if (!philo)
		return (NULL);
	philo->fork_left = (t_mutex_value *)new_mutex();
	if (!philo->fork_left)
	{
		free(philo);
		philo = NULL;
		return (NULL);
	}
	philo->dead_flag = dead_flag;
	philo->num_philos = args[0];
	philo->time_die = args[1];
	philo->time_eat = args[2];
	philo->time_sleep = args[3];
	philo->delay = set_delay(args);
	philo->num_loops = args[4];
	if (!philo->num_loops)
		philo->num_loops = -1;
	philo->num = num;
	philo->start_time = now();
	return (philo);
}

// Initializes the threads from the philosophers and assing right forks.
//If something failes, returns 1, otherwise, returns 0.
int	init_threads(t_philo **philo, int num_threads)
{
	int	i;

	i = 0;
	while (i < num_threads)
	{
		if (i + 1 == num_threads)
			philo[i]->fork_right = philo[0]->fork_left;
		else
			philo[i]->fork_right = philo[i + 1]->fork_left;
		if (pthread_create(&philo[i]->philo, NULL, philo_routine, philo[i]))
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
t_philo	**init_philos(t_mutex_value *dead_flag, size_t *args)
{
	size_t	num;
	t_philo	**res;

	num = 0;
	res = ft_calloc(sizeof(t_philo *), args[0] + 1);
	if (!res)
		return (NULL);
	while (num < args[0])
	{
		res[num] = new_philo(dead_flag, args, num + 1);
		if (!res[num])
			return (NULL);
		++num;
	}
	return (res);
}
