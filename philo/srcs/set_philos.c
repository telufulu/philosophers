/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:50:33 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/11 22:44:19 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_eat(t_philo *philo, long int start_time)
{
	long int	check;
	
	if (philo->num % 2)
		usleep(5000);
	philo->flags |= THINK;
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->prev->fork);
	while (philo->flags & DEAD)
	{
		if (get_time() - start_time >= philo->config->time_die)
		{
			philo->flags |= DEAD;
			return ;
		}
	}
	philo->flags |= EAT;
	check = get_time() - start_time;
	while (check < philo->config->time_eat)
		check = get_time() - start_time;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->prev->fork);
}

void	philo_sleep(t_philo *philo, long int start_time)
{
	long int	check;

	check = get_time() - start_time;
	philo->flags |= SLEEP;
	while (check < philo->config->time_sleep)
		check = get_time() - start_time;
		;
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->config->dead_flag)
	{
		if (!(philo->flags & DEAD))
			philo_eat(philo, get_time());
		if (!(philo->flags & DEAD))
			philo_sleep(philo, get_time());
	}
	return (0);
}

t_philo	*first_philo(t_philo *aux, t_philo *res)
{
	while (res->prev)
		res = res->prev;
	res->prev = aux;
	aux->next = res;
	return (res);
}

t_philo	*create_philos(t_config *config)
{
	t_philo	*res;
	t_philo	*aux;
	int		i;

	res = 0;
	i = 0;
	while (++i <= config->num_philos)
	{
		aux = res;
		res = ft_calloc(sizeof(t_philo), 1);
		if (!res)
			return (0);
		if (aux)
			aux->next = res;
		res->prev = aux;
		res->num = i;
		res->config = config;
		if (pthread_mutex_init(&res->fork, NULL))
			return (0);
		pthread_create(&res->philo, NULL, philo_routine, res);
	}
	return (first_philo(aux, res));
}
