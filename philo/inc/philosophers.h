/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:45:25 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/28 16:04:20 by telufulu         ###   ########.fr       */
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
# include <errno.h>

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
	long int		num_eats;
	int				num_philos;
	long int		time_die;
	long int		time_eat;
	long int		time_sleep;
	long int		start_time;	
	long int		num_loops;	
	pthread_mutex_t	stop;
}				t_config;

typedef struct s_philo
{
	struct s_philo	*prev;
	pthread_t		philo;
	char			fork_flag;
	pthread_mutex_t	fork;
	int				num;
	long int		tm_alive;
	t_config		*config;
	struct s_philo	*next;
}				t_philo;

// main.c

// routines.c
int			take_forks(t_philo *philo);
int			drop_forks(t_philo *philo);
int			philo_eat(t_philo *philo, int *loop);
int			philo_sleep(t_philo *philo);

// routines_utils.c
void		add_eat(t_philo *philo);
int			check_dead(t_philo *philo);
int			lock_fork(t_philo *philo);
void		unlock_fork(t_philo *philo);

// set_philos.c
t_philo		*set_philos(t_config *config, int start_philo);
int			start_routines(t_philo *philos, t_config *config);
int			wait_philos(t_philo *philos, t_config *config);

// utils.c
long int	get_time(void);
int			get_config(t_config *config, char **argv);
int			check_flags(t_config *config);
int			print_msg(int philo, int flag, t_config *config);

// libft_utils.c
int			ft_isspace(int c);
long int	ft_atolui(const char *str);
int			ft_error(char *err);
size_t		ft_strlen(const char *s);
void		*ft_calloc(size_t count, size_t size);

#endif
