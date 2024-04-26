/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:11:11 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/25 23:32:30 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_dead(t_config *config, long int time_alive)
{
	pthread_mutex_lock(&config->stop);
	if (!config->dead_flag && get_time() - time_alive >= config->time_die)
		++config->dead_flag;
	pthread_mutex_unlock(&config->stop);
	return (config->dead_flag);
}

void 	wait_philos(t_philo *philo, int n)
{
	int	i;

	i = n;
	while (--n)
	{
		pthread_create(&philo->philo, NULL, philo_routine, philo);
		philo = philo->next;
	}
	while (--i)
	{
		pthread_join(philo->philo, NULL);
		philo = philo->next;
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
		wait_philos(philos, config->num_philos);
	}
	else
		ft_error("wrong number of arguments. Expected 5 or 6\n");
	return (0);
}
