/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:08:56 by telufulu          #+#    #+#             */
/*   Updated: 2024/05/03 21:25:43 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Gets main arguments, check them and assign them to an array.
// If some of the numbers are not uint64_t, it returns 0.
int	get_args(char **argv, ssize_t *args)
{
	if (!only_digs(argv))
		return (ft_error("only numeric arguments"));
	args[0] = ft_atolui(argv[0]);
	args[1] = ft_atolui(argv[1]);
	args[2] = ft_atolui(argv[2]);
	args[3] = ft_atolui(argv[3]);
	if (args[0] > 200 || args[1] < 60 || args[2] < 60 || args[3] < 60)
		return (ft_error("maximum 200 philos, minimum value for args is 60"));
	if (argv[4])
		args[4] = ft_atolui(argv[4]);
	if (!argv[4] || !args[4])
		args[4] = -1;
	args[5] = args[0];
	return (0);
}

static bool	str_is_digit(char *str)
{
	while (str && *str)
	{
		if (*str < '0' || *str > '9')
			return (false);
		++str;
	}
	return (true);
}

// Check args. If it finds a non digit character, returns false. Otherwise,
// returns true.
bool	only_digs(char **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i])
	{
		if (!str_is_digit(argv[i]))
			return (false);
		++i;
	}
	return (true);
}
