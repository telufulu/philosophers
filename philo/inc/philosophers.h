/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:45:25 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/26 17:29:53 by telufulu         ###   ########.fr       */
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
# include <sys/time.h>

// Philo flags
# define NO_CHANGE 	0
# define FORK 		1
# define EAT 		2
# define SLEEP 		4
# define THINK		8
# define DEAD		16

typedef struct s_config
{
	char			dead_flag;
	int				num_philos;
	long int		time_die;
	long int		time_eat;
	long int		time_sleep;
	long int		start_time;	
	pthread_mutex_t	stop;
}				t_config;

typedef struct s_philo
{
	struct s_philo	*prev;
	pthread_t		philo;
	pthread_mutex_t	fork;
	int				num;
	long int		tm_alive;
	t_config		*config;
	struct s_philo	*next;
}				t_philo;

// main.c

// routines.c

// set_philos.c

// utils.c
int			check_args(char **argv);

// libft_utils.c
int			ft_isspace(int c);
long int	ft_atoli(const char *str);
int			ft_error(char *err);
size_t		ft_strlen(const char *s);
void		*ft_calloc(size_t count, size_t size);

#endif
