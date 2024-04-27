/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:50:33 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/27 14:19:13 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*list_union(t_philo *first, t_philo *last)
{
	if (!first)
		return (last);
	while (first->prev)
		first = first->prev;
	last->next = first;
	first->prev = last;
	return (first);
}

t_philo	*set_philos(t_config *config, int start_philo)
{
	t_philo	*aux;
	t_philo	*res;

	aux = 0;
	while (start_philo <= config->num_philos)
	{
		res = aux;
		aux = ft_calloc(sizeof(t_philo), 1);
		if (!aux)
			return (NULL);
		if (pthread_mutex_init(&aux->fork, NULL))
			return (NULL);
		aux->num = start_philo;
		aux->config = config;
		aux->prev = res;
		if (res)
			res->next = aux;
		++start_philo;
	}
	return (list_union(res, aux));
}
