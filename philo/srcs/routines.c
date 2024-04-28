/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 20:43:12 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/27 21:54:57 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_forks(t_philo *philo)
{
	if (philo->num % 2)
	{
		pthread_mutex_lock(&philo->prev->fork);
		/*while (pthread_mutex_lock(&philo->prev->fork) == EBUSY)
		{
			printf("philo %i is trying to catch a fork", philo->num);
			sleep(1);
		}*/
		print_msg(philo->num, FORK, philo->config);
		if (check_dead(philo))
			return (1);
	}
	pthread_mutex_lock(&philo->fork);
	print_msg(philo->num, FORK, philo->config);
	if (check_dead(philo))
		return (1);
	if (!(philo->num % 2))
	{
		pthread_mutex_lock(&philo->prev->fork);
		/*while (pthread_mutex_lock(&philo->prev->fork) == EBUSY)
		{
			printf("philo %i is trying to catch a fork", philo->num);
			sleep(1);
		}*/
		print_msg(philo->num, FORK, philo->config);
		if (check_dead(philo))
			return (1);
	}
	return (0);
}

int	drop_forks(t_philo *philo)
{
	if (philo->num % 2)
		pthread_mutex_unlock(&philo->prev->fork);
	pthread_mutex_unlock(&philo->fork);
	if (!(philo->num % 2))
		pthread_mutex_unlock(&philo->prev->fork);
	return (0);
}

int	philo_eat(t_philo *philo, int loop)
{
	philo->tm_alive = get_time();
	print_msg(philo->num, EAT, philo->config);
	if (loop == philo->config->num_loops)
		add_eat(philo);
	while (get_time() - philo->tm_alive < philo->config->time_eat &&\
		!check_dead(philo) && !check_flags(philo->config))
		usleep(420);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	print_msg(philo->num, SLEEP, philo->config);
	while (get_time() - philo->tm_alive < philo->config->time_sleep &&\
		!check_dead(philo) && !check_flags(philo->config))
		usleep(420);
	return (0);
}
