/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 21:53:57 by telufulu          #+#    #+#             */
/*   Updated: 2024/05/03 21:10:11 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_mutex_value	*dead_flag;
	ssize_t			args[6];
	t_philo			**philos;

	if (argc != 5 && argc != 6)
		return (ft_error("wrong number of arguments. Max 6, min 5"));
	dead_flag = new_mutex();
	if (!dead_flag)
		return (free_mutex(dead_flag), ft_error("pthread.h failed"));
	if (get_args(argv + 1, args))
		return (free_mutex(dead_flag), -1);
	philos = init_philos(dead_flag, args);
	if (!philos)
		return (free_all(dead_flag, philos), \
			ft_error("failed making philos"));
	if (init_threads(philos, args[0]))
		return (free_all(dead_flag, philos), \
			ft_error("init threads failed"));
	if (wait_philos(philos, args[0]))
		return (free_all(dead_flag, philos), 0);
	free_all(dead_flag, philos);
	return (0);
}
