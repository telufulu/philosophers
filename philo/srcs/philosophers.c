/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:11:11 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/25 19:39:09 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_dead(t_config *config)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&config->stop);
	if (config->dead_flag)
		++i;
	pthread_mutex_unlock(&config->stop);
	return (i);
}

void 	wait_philos(t_philo *philo, int n)
{
	while (--n)
	{
		pthread_create(&philo->philo, NULL, philo_routine, philo);
		pthread_join(philo->philo, NULL);
		philo = philo->next;
	}
}

int	main(int argc, char **argv)
{
	t_config	*config;
	t_philo		*philos;
	int			check;

	check = 0;
	if (argc == 5 || argc == 6)
	{
		config = get_config(argv);
		if (!config)
			ft_error("Configuration settings failed\n");
		philos = create_philos(config);
		if (!philos)
			ft_error("Creation of threads failed\n");
		wait_philos(philos, config->num_philos);
		//while (1)
		//	check = 1;
		//while (!check)
		//	check = check_dead(config);	
	}
	else
		ft_error("wrong number of arguments. Expected 5 or 6\n");
	return (0);
}
