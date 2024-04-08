/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:04:09 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/08 21:09:22 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>

int	main()
{
	struct timeval 	start;
	struct timeval	current;
	size_t	time;

	gettimeofday(&start, NULL);
	time = start.tv_sec * 1000 + start.tv_usec;
	printf("time: %zu\n", time);
	printf("start time: %.2ld\n", start.tv_sec);
	current.tv_usec = start.tv_usec;
	//while (current.tv_usec < start.tv_usec)
	//	gettimeofday(&current, NULL);
	//printf("time: %.2d\n", current.tv_usec - start.tv_usec);
	return (0);
}
