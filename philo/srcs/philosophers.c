/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 21:53:57 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/29 16:45:55 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_mutex_value	*dead_flag;
	size_t			args[5];
	t_philo			*philos;

	if (argc == 5 || argc == 6)
	{
		dead_flag = new_mutex();
		if (!dead_flag)
			return (ft_error("pthread.h failed"));
		if (get_args(argv + 1, args))
			return (ft_error("malloc error"));
		philos = init_philos(dead_flag, args); 
		if (!philos)
			return (ft_error("failed making philos"));
		if (init_threads(philos, args[0]))
			return (ft_error("failed making philos"));
		if (wait_philos(philos))
			return (0);
		/*int check = wait_philos(philos);
		if (!check)
			return (ft_error("pthread.h failed"));
		*/
	}
	else
		return (ft_error("wrong number of arguments"));
	return (0);
}
