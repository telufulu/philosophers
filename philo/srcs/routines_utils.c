/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 20:42:10 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/27 20:43:04 by telufulu         ###   ########.fr       */
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
