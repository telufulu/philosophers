/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:50:33 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/19 18:28:51 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*add_philo(t_philo *res;)
{
	t_philo	*aux;
	t_philo

	aux = res;
	while (aux->next)
		aux = aux->next;
}

t_philo	*create_philos(t_config *config)
{
	t_philo	*res;
	int		i;

	i = 0;
	res = 0;
	while (++i <= config->num_philos)
	{
		res = add_philo();
	}
	return (res);
}
