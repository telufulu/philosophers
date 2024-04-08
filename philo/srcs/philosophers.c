/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:45:52 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/07 19:00:39 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*say_hi(void *arg)
{
	int	i;

	i = 10;
	while (--i)
	{
		usleep(1000000);
		printf("Hi! I'm %p\n", arg);
	}
	arg->flags = arg->flags & DEAD;
	return (0);
}

t_philo	*new_thread(t_philo *philo)
{
	t_philo	*aux;

	aux = ft_calloc(sizeof(t_philo), 1);
	if (!aux)
		return (NULL);
	aux->prev = philo;
	pthread_create(&aux->philo, NULL, say_hi, aux);
	return (aux);
}

void	create_philos(t_philo **first, int num_of_philos)
{
	t_philo	*aux;
	
	(*first) = new_thread(NULL);
	aux = (*first);
	while (--num_of_philos)
	{
		aux->next = new_thread(aux);
		aux = aux->next;
	}
	(*first)->prev = aux;
	aux->next = (*first);
}

void	*print_status(void *arg)
{
	pthread_t	*philos;

	philos = (ptherad_t *)arg;
	while (!(philos->flags & 16))
	{
		if (philos->flags & FORK)
			printf("%i has taken a fork", philos->num_philo);
		if (philos->flags & EAT)
			printf("%i is eating", philos->num_philo);
		if (philos->flags & SLEEP)
			printf("%i is sleaping", philos->num_philo);
		if (philos->flags & THINK)
			printf("%i is thinking", philos->num_philo);
		philos = philos->next;
	}
	if (philos->flags & DEAD)
		printf("%i is dead", philos->num_philo);
}

int	main(int argc, char **argv)
{
	t_philo	*philosophers;
	pthread_t	msg;

	philosophers = NULL;
	if (argc == 5 || argc == 6)
	{
		create_philos(&philosophers, ft_atoi(argv[1]));
		if (!philosophers || !philosophers->prev)
			return (ft_error("Fallo al crear hilo"));
		pthread_create(&msg, NULL, print_status, philosophers);
		pthread_join(philosophers->philo, NULL);
	}
	else
		return (ft_error(argv[1]));
	return (0);
}
