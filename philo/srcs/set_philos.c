/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:50:33 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/25 22:39:25 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philo(t_philo *prev, t_philo *res, int num, t_config *config)
{
	res->prev = prev;
	if (prev)
		prev->next = res;
	res->num = num;
	res->config = config;
	if (pthread_mutex_init(&res->fork, NULL))
		return (1);
	return (0);
}

int	free_list(t_philo *res)
{
	while (res->prev)
	{
		res = res->prev;
		free(res->next);
		res->next = NULL;
	}
	free(res);
	res = 0;
	return (1);
}

int	add_philo(t_philo *res, int i, t_config *config)
{
	while (res->next)
		res = res->next;
	res->next = ft_calloc(sizeof(t_philo), 1);
	if (!res->next)
		return (free_list(res));
	if (init_philo(res, res->next, i, config))
		return (free_list(res));
	return (0);
}

void	unit_list(t_philo *res)
{
	t_philo	*aux;

	aux = res;
	while (aux->next)
		aux = aux->next;
	res->prev = aux;
	aux->next = res;
}

t_philo	*create_philos(t_config *config)
{
	t_philo	*res;
	int		i;

	i = 1;
	res = ft_calloc(sizeof(t_philo), 1);
	if (!res)
		return (NULL);
	init_philo(0, res, i, config);
	while (++i <= config->num_philos)
		if (add_philo(res, i, config))
			return (NULL);
	unit_list(res);
	return (res);
}
