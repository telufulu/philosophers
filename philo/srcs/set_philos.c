/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:50:33 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/12 21:47:45 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	return (first_philo(res, res));
}
