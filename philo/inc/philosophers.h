/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:45:25 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/07 18:52:01 by telufulu         ###   ########.fr       */
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
# define NO_CHANGE 	00000000
# define FORK 		00000001
# define EAT 		00000010
# define SLEEP 		00000100
# define THINK		00001000
# define DEAD		00010000

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
void		create_philos(t_philo **first, int num_of_philos);
t_philo		*new_thread(t_philo *philo);
void		*say_hi(void *arg);

// libft_utils.c
int		ft_isspace(int c);
int		ft_atoi(const char *str);
int		ft_error(char *err);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);

#endif
