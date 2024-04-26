/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:12:36 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/26 17:29:51 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(char **argv)
{
	int	i;

	i = 0;
	while (argv)
	{
		while (**argv >= '0' && *argv <= '9')
		{
			if (**argv < '0' || *argv > '9')
				return (-1);
			++(*argv);
		}
		++argv;
	}
	return (0);
}
