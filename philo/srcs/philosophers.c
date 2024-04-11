/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:11:11 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/11 17:42:04 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_config	*config;
	t_philo		*philos;

	if (argc == 5 || argc == 6)
	{
		config = get_config(argv);
		if (!config)
			ft_error("Configuration settings failed\n");
		philos = create_philos(config);
		pthread_join(philos->philo, NULL);
	}
	else
		ft_error("wrong number of arguments. Expected 5 or 6\n");
	return (0);
}
