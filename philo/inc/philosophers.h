/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 21:54:29 by telufulu          #+#    #+#             */
/*   Updated: 2024/05/01 22:15:17 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/******************************************************************************
 * Includes
 *****************************************************************************/
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <errno.h>
# include <stdbool.h>
# include <stdint.h>

/******************************************************************************
 * Structs
 *****************************************************************************/

typedef struct s_mutex_value
{
	pthread_mutex_t	mutex;
	bool			value;
}		t_mutex_value;

typedef struct s_philo
{
	pthread_t		philo;
	t_mutex_value	*fork_left;
	t_mutex_value	*fork_right;
	t_mutex_value	*dead_flag;
	size_t			num_philos;
	uint64_t		time_die;
	uint64_t		time_eat;
	uint64_t		time_sleep;
	uint64_t		time_alive;
	ssize_t			num_loops;
	int				num;
	uint64_t		start_time;
}				t_philo;

/******************************************************************************
 * Functions
 *****************************************************************************/

//utils.c
bool			change_value(t_mutex_value *mutex, bool new_value);
t_mutex_value	*new_mutex(void);
t_philo			*new_philo(t_mutex_value *dead_flag, size_t *args, int num);
int				init_threads(t_philo **philo, int num_threads);
int				get_args(char **argv, size_t *args);
t_philo			**init_philos(t_mutex_value *dead_flag, size_t *args);
bool			wait_philos(t_philo **philos);
uint64_t		now(void);
void			time_sleep(uint64_t msecs);
bool			is_dead(t_philo *philo);
bool			check_dead(t_philo *philo);
void			print_msg(t_mutex_value *stop, char *msg, t_philo *philo);
void			free_mutex(t_mutex_value *mutex);
void			free_all(t_mutex_value *dead, t_philo **philos);

// routines.c
void			*philo_routine(void *arg);

// libft_utils.c
long int		ft_atolui(const char *str);
void			*ft_calloc(size_t count, size_t size);
size_t			ft_strlen(const char *s);
int				ft_error(char *err);

#endif
