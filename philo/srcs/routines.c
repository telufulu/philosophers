/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 20:43:12 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/25 19:21:03 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_state(t_philo *philo, int flag)
{
	pthread_mutex_lock(&(philo->config)->stop);
	if (flag == DEAD || get_time() - philo->tm_alive > philo->config->time_die)
	{
		++philo->config->dead_flag;
		pthread_mutex_unlock(&(philo->config)->stop);
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
	pthread_mutex_unlock(&(philo->config)->stop);
	return (0);
}

int	take_forks(t_philo *philo, int flag)
{
	if (flag % 2)
	{
		//printf("PAR");
		pthread_mutex_lock(&philo->fork);
		//if (print_state(philo, FORK))
		//	return (1);
		//pthread_mutex_lock(&(philo->prev)->fork);
		printf("%d -> %p\n", philo->num, philo->prev);
		//if (print_state(philo, FORK))
		//	return (1);
	}
	else
	{
		pthread_mutex_lock(&(philo->prev)->fork);
		//if (print_state(philo, FORK))
		//	return (1);
		pthread_mutex_lock(&philo->fork);
		//if (print_state(philo, FORK))
		//	return (1);
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
	//while (!check_dead(philo->config))
	while (1)
	{
		if (take_forks(philo, philo->num) == DEAD)
			return (NULL);
			//print_state(philo, DEAD);
		else
		{
			//philo->tm_alive = get_time();
			//if (philo_eat(philo) == DEAD)
			//return (NULL);
			//	++philo->config->dead_flag;
		}
	}
	printf("Sale\n");
	return (NULL);
} 
