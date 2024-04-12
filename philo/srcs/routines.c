/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 20:43:12 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/13 00:28:43 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_dead(t_philo *philo, long int *time_dying)
{
	if (get_time() - *time_dying >= philo->config->time_die)
	{
		philo->flags |= DEAD;
		philo->config->dead_flag = 1;
		print_msg(philo);
		return (1);
	}
	return (0);
}

void	philo_eat(t_philo *philo, long int *time_dying)
{
	print_msg(philo);
	philo->flags |= EAT;
	while (!(philo->flags & DEAD) && \
		get_time() - *time_dying < philo->config->time_eat)
		check_dead(philo, time_dying);
}

void	philo_sleep(t_philo *philo, long int *time_dying)
{
	print_msg(philo);
	philo->flags |= SLEEP;
	while (!(philo->flags & DEAD) && \
		get_time() - *time_dying < philo->config->time_sleep + philo->config->time_eat)
		check_dead(philo, time_dying);
}

void	philo_think(t_philo *philo)
{
	print_msg(philo);
	philo->flags |= THINK;
}

void	get_forks(t_philo *philo, long int *time_dying)
{
	if (check_dead(philo, time_dying))
		return ;
	pthread_mutex_lock(&philo->fork);
	printf("%lims %i has taken a fork\n", \
		get_time() - philo->config->start_time, philo->num);
	if (check_dead(philo, time_dying))
		return ;
	pthread_mutex_lock(&philo->prev->fork);
	printf("%lims %i has taken a fork\n", \
		get_time() - philo->config->start_time, philo->num);
	if (check_dead(philo, time_dying))
		return ;
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;
	long int	time_dying;

	philo = (t_philo *)arg;
	time_dying = get_time();
	if (philo->num % 2)
		usleep(1000);
	while (!philo->config->dead_flag)
	{
		get_forks(philo, &time_dying);
		time_dying = get_time();
		if (!(philo->flags & DEAD) && !philo->config->dead_flag)
			philo_eat(philo, &time_dying);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->prev->fork);
		if (!(philo->flags & DEAD) && !philo->config->dead_flag)
			philo_sleep(philo, &time_dying);
		if (!(philo->flags & DEAD) && !philo->config->dead_flag)
			philo_think(philo);
	}
	return (0);
}
