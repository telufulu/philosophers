/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:11:11 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/26 17:30:01 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	//t_philo		*philos;
	//t_config	config;

	if (argc == 5 || argc == 6)
	{
		if (check_args(argv + 1))
			return (-1);
	}
	else
		return (ft_error("wrong number of arguments"));
	return (0);
}
