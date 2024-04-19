/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:11:11 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/19 19:42:54 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	lock_threads(t_philo *philos, int num_philos)
{
	while (num_philos--)
	{
		pthread_join(philos->philo, NULL);
		philos = philos->next;
	}
}

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
		if (!philos)
			ft_error("Creation of threads failed\n");
		lock_threads(philos, config->num_philos);
	}
	else
		ft_error("wrong number of arguments. Expected 5 or 6\n");
	return (0);
}
