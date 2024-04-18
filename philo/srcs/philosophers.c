/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:11:11 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/18 21:02:07 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_config	*config;
	t_philo		*philos;
	pthread_t	msg;

	if (argc == 5 || argc == 6)
	{
		config = get_config(argv);
		if (!config)
			ft_error("Configuration settings failed\n");
		philos = create_philos(config);
		if (!philos)
			ft_error("Creation of threads failed\n");
		pthread_create(&msg, NULL, print_msg, philos);
		pthread_join(msg, NULL);
	}
	else
		ft_error("wrong number of arguments. Expected 5 or 6\n");
	return (0);
}
