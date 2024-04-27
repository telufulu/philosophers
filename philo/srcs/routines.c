/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 20:43:12 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/27 19:06:49 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	add_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->config->stop);
	++philo->config->num_eats;
	pthread_mutex_unlock(&philo->config->stop);
}

int	check_dead(t_philo *philo)
{
	if (get_time() - philo->tm_alive >= philo->config->time_die)
		return (print_msg(philo->num, DEAD, philo->config));
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (philo->num % 2)
	{
		pthread_mutex_lock(&philo->prev->fork);
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

static void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		loop;

	philo = (t_philo *)arg;
	loop = 0;
	philo->tm_alive = get_time();
	printf("philo %i start loop", philo->num);
	while (!check_flags(philo->config) && ++loop)
	{
		if (take_forks(philo))
			return (NULL);
		if (loop == philo->config->num_loops)
			add_eat(philo);
		sleep(1);
	}
	return (NULL);
}

int	start_routines(t_philo *philos, t_config *config)
{
	int	num_philos;

	pthread_mutex_lock(&config->stop);
	num_philos = config->num_philos;
	while (num_philos--)
	{
		if (pthread_create(&philos->philo, NULL, philo_routine, philos))
			return (-1);
		philos = philos->next;
	}
	num_philos = config->num_philos;
	while (num_philos--)
	{
		pthread_join(philos->philo, NULL);
		//if (pthread_join(philos->philo, NULL))
			//return (-1);
		printf("num_philos: %i\n", num_philos);
		philos = philos->next;
	}
	pthread_mutex_unlock(&config->stop);
	return (0);
}
