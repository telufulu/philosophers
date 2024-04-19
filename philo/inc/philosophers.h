/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:45:25 by telufulu          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/04/18 21:02:09 by telufulu         ###   ########.fr       */
=======
/*   Updated: 2024/04/13 00:25:00 by telufulu         ###   ########.fr       */
>>>>>>> c05ba487d7061c8cb137341d53f8dd5ce1c4984f
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
	char		dead_flag;
	int			num_philos;
	long int	time_die;
	long int	time_eat;
	long int	time_sleep;
	long int	start_time;	
}				t_config;

typedef struct s_philo
{
	struct s_philo	*prev;
	pthread_t		philo;
	pthread_mutex_t	fork;
	int				num;
	char			flags;
	t_config		*config;
	struct s_philo	*next;
}				t_philo;

// main.c

// routines.c
int		check_dead(t_philo *philo, long int *time_dying);
void	philo_eat(t_philo *philo, long int *time_dying);
void	philo_sleep(t_philo *philo, long int *time_dying);
void	*philo_routine(void *arg);

// set_philos.c
t_philo	*create_philos(t_config *config);

// utils.c
t_config	*get_config(char **argv);
long int	get_time(void);
void		print_msg(t_philo *philos);

// libft_utils.c
int			ft_isspace(int c);
long int	ft_atoli(const char *str);
int			ft_error(char *err);
size_t		ft_strlen(const char *s);
void		*ft_calloc(size_t count, size_t size);

#endif
