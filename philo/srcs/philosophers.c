/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:11:11 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/27 20:12:44 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_philo		*philos;
	t_config	config;

	if (argc == 5 || argc == 6)
	{
		if (get_config(&config, argv + 1))
			return (ft_error("arguments must be unsigned int greater than 0"));
		philos = set_philos(&config, 1);
		if (!philos)
			return (ft_error("malloc or mutex failed"));
		if (start_routines(philos, &config))
			return (ft_error("threads failed"));
		/*while (philos->next)
		{
			sleep(1);
			printf("I'm philo %i\n", philos->num);
			philos = philos->next;
		}*/
	}
	else
		return (ft_error("wrong number of arguments"));
	return (0);
}
