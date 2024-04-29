/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 00:56:03 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/29 01:59:02 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (philos->dead_flag->value == false)
	{
		printf("I'm philo %i\n", philos->num);
		time_sleep(500);
	}
	return (NULL);
}
