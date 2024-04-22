/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 20:43:12 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/20 12:14:05 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_state(t_philo *philo, int flag)
{
	if (flag == DEAD || get_time() - philo->time_alive > philo->config->time_die)
	{
		pthread_mutex_lock(&config->stop);
		++philo->config->dead_flag;
		pthread_mutex_unlock(&config->stop);
		printf("philo %i is dead\n", philo->num);
		return (DEAD);
	}
	else if (flag == FORK)
		printf("philo %i has taken a fork\n", philo->num);
	else if (flag == EAT)
		printf("philo %i is eating\n", philo->num);
	else if (flag == SLEEP)
		printf("philo %i is sleeping\n", philo->num);
	else if (flag == THINK)
		printf("philo %i is thinking\n", philo->num);
	return (0);
}

int	take_forks(t_philo *philo, int flag)
{
	if (flag)
	{
		pthread_mutex_lock(&philo->fork);
		if (print_state(philo, FORK))
			return (1);
		pthread_mutex_lock(&philo->prev->fork);
		if (print_state(philo, FORK))
			return (1);
	}
	else
	{
		pthread_mutex_lock(&philo->prev->fork);
		if (print_state(philo, FORK))
			return (DEAD);
		pthread_mutex_lock(&philo->fork);
		if (print_state(philo, FORK))
			return (DEAD);
	}
	pthread_mutex_unlock(&philo->prev->fork);
	pthread_mutex_unlock(&philo->fork);
	return (0);
}

int		philo_eat(t_philo *philo)
{
	int	start;

	start = get_time();
	while (get_time() - start < philo->config->time_eat)
		if (get_time() - philo->start_time > philo->config->time_die)
			return (print_state(philo, DEAD));
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->time_alive = get_time();
	while (check_dead(philo->config))
	{
		if (take_forks(philo, philo->num % 2) == DEAD)
			return (NULL);
		philo->time_alive = get_time();
		if (philo_eat(philo) == DEAD)
			return (NULL);
	}
	return (NULL);
} 
