/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:41:30 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/26 23:34:00 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	ft_atolui(const char *str)
{
	long int	res;

	res = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	while (*str == '0')
		str++;
	if (*str < '0' || *str > '9')
		return (res);
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		res *= 10;
		res += (*str - '0');
		str++;
	}
	return (res);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;
	char	*aux;
	size_t	len;

	len = count * size;
	res = malloc(len);
	if (!res)
		return (0);
	aux = (char *)res;
	while (--len)
		aux[len] = 0;
	aux[len] = 0;
	return (res);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i] != '\0')
		i++;
	return (i);
}

int	ft_error(char *err)
{
	write(2, "\x1b[31mError\x1b[0m: ", 16);
	if (err && *err)
	{
		write(2, err, ft_strlen(err));
		write(2, "\n", 1);
	}
	return (-1);
}
