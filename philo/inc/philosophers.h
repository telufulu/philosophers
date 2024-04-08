/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:45:25 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/08 16:52:13 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/*
 * BORRAR ANTES DE ENTREGAR 
 */
/**************************/

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>


// Philo flags
# define NO_CHANGE 	0
# define FORK 		1
# define EAT 		2
# define SLEEP 		4
# define THINK		8
# define DEAD		16

typedef struct s_philo
{
	void			*prev;
	pthread_t		philo;
	pthread_mutex_t	fork;
	int				num_philo;
	char			flags;
	void			*next;
}				t_philo;

// main.c

// libft_utils.c
int		ft_isspace(int c);
int		ft_atoi(const char *str);
int		ft_error(char *err);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);

#endif
