/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 20:43:12 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/23 20:37:04 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_state(t_philo *philo, int flag)
{
	if (flag == DEAD || get_time() - philo->tm_alive > philo->config->time_die)
	{
		pthread_mutex_lock(&philo->config->stop);
		++philo->config->dead_flag;
			pthread_mutex_unlock(&philo->config->stop);
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
			return (1);
		pthread_mutex_lock(&philo->fork);
		if (print_state(philo, FORK))
			return (1);
	}
	sleep(1);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->prev->fork);
	return (0);
}

//int		philo_eat(t_philo *philo)
//{
//}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->tm_alive = get_time();
	while (!check_dead(philo->config))
	{
		if (take_forks(philo, philo->num % 2) == DEAD)
			print_state(philo, DEAD);
		else
		{
			philo->tm_alive = get_time();
			//if (philo_eat(philo) == DEAD)
			//	++philo->config->dead_flag;
		}
	}
	return (NULL);
} 
