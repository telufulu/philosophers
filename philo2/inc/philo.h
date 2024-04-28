#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <errno.h>
# include <stdbool.h>

typedef struct s_philo t_philo;

typedef struct s_secured_value
{
	pthread_mutex_t 	mutex;
	bool 				value;
}
 t_secured_value;

typedef struct s_config
{
	size_t 				num_philos;
	t_secured_value		*someone_dead;
	size_t				eat_time;
	size_t 				die_time;
	size_t				sleep_time;
	size_t 				start_time;
	ssize_t 			loop_times;
	pthread_mutex_t 	print_mutex;
	t_philo 			*philos;
} t_config;

typedef struct s_philo
{
	pthread_t 			pid;
	int 				num;
	size_t              eat_time;
	size_t              die_time;
 	size_t				sleep_time;
	uint64_t			alive_time;
	uint64_t            start_time;
	ssize_t             loop_times;
	t_secured_value 	*someone_dead;
	pthread_mutex_t 	*print_mutex;
	t_secured_value		*fork_left;
	t_secured_value		*fork_right;
} t_philo;

long int 	ft_atolui(const char *str);
void 		*ft_calloc(size_t count, size_t size);
size_t 		ft_strlen(const char *s);
int 		ft_error(char *err);

#endif
