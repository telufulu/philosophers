/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:45:25 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/11 17:42:13 by telufulu         ###   ########.fr       */
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
	char	dead_flag;
	size_t	time_die;
	size_t	time_eat;
	size_t	time_sleep;
	size_t	start_time;	
	int		num_philos;
}				t_config;

typedef struct s_philo
{
	struct s_philo	*prev;
	pthread_t		philo;
	pthread_mutex_t	fork;
	int				num_philo;
	char			flags;
	t_config		*config;
	struct s_philo	*next;
}				t_philo;

// main.c

// set_philos.c
t_philo	*create_philos(t_config *config);
void	*philo_routine(void *arg);

// utils.c
t_config	*get_config(char **argv);
size_t		get_time(void);

// libft_utils.c
int		ft_isspace(int c);
int		ft_atoi(const char *str);
int		ft_error(char *err);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);

#endif
