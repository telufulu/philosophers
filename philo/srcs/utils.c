/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:12:36 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/11 15:51:06 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_config	*get_config(char **argv)
{
	t_config	*res;

	res = ft_calloc(sizeof(t_config), 1);
	if (!res)
		return (0);
	res->num_philos = ft_atoi(argv[1]);
	res->time_die = ft_atoi(argv[2]);
	res->time_eat = ft_atoi(argv[3]);
	res->time_sleep = ft_atoi(argv[4]);
	res->start_time = get_time();
	return (res);
}

size_t	get_time(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return (start.tv_sec * 1000 + start.tv_sec);
}
