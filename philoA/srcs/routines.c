/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 20:43:12 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/25 23:59:55 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_state(t_philo *philo, int flag)
{
	long int	time;

	time = get_time() - philo->config->start_time;
	if (flag == DEAD || check_dead(philo->config, philo->tm_alive))
	{
		printf("%lims\tphilo %i is dead\n", time, philo->num);
		return (DEAD);
	}
	pthread_mutex_lock(&(philo->config)->stop);
	if (flag == FORK)
		printf("%lims\tphilo %i has taken a fork\n", time, philo->num);
	else if (flag == EAT)
		printf("%lims\tphilo %i is eating\n", time, philo->num);
	else if (flag == SLEEP)
		printf("%lims\tphilo %i is sleeping\n", time, philo->num);
	else if (flag == THINK)
		printf("%lims\tphilo %i is thinking\n", time, philo->num);
	pthread_mutex_unlock(&(philo->config)->stop);
	return (0);
}

int	take_forks(t_philo *philo, int philo_num)
{
	if (philo_num % 2)
	{
		pthread_mutex_lock(&philo->fork);
		if (print_state(philo, FORK) == DEAD)
			return (1);
		pthread_mutex_lock(&(philo->prev)->fork);
		if (print_state(philo, FORK) == DEAD)
			return (1);
	}
	else
	{
		pthread_mutex_lock(&(philo->prev)->fork);
		if (print_state(philo, FORK) == DEAD)
			return (1);
		pthread_mutex_lock(&philo->fork);
		if (print_state(philo, FORK) == DEAD)
			return (1);
	}
	//pthread_mutex_unlock(&philo->fork);
	//pthread_mutex_unlock(&philo->prev->fork);
	return (0);
}

int		philo_eat(t_philo *philo, t_config *config)
{
	print_state(philo, EAT);
	while (get_time() - philo->tm_alive < config->time_eat)
	{
		if (check_dead(config, philo->tm_alive))
			return (print_state(philo, DEAD));
		usleep(42);
	}
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->tm_alive = get_time();
	while (!check_dead(philo->config, philo->tm_alive))
	{
		if (take_forks(philo, philo->num))
			return (NULL);
	}
	return (NULL);
} 
