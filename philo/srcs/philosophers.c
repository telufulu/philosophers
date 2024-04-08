/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:45:52 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/08 16:52:12 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*say_hi(void *arg)
{
	t_philo	*aux;
	int	i;

	i = 10;
	aux = (t_philo *)arg;
	while (--i)
	{
		usleep(1000000);
		if (aux->num_philo == 5 && i == 6)
			aux->flags |= DEAD;
	}
	return (0);
}

t_philo	*new_thread(t_philo *philo, int num)
{
	t_philo	*aux;

	aux = ft_calloc(sizeof(t_philo), 1);
	if (!aux)
		return (NULL);
	aux->prev = philo;
	aux->num_philo = num;
	pthread_create(&aux->philo, NULL, say_hi, aux);
	return (aux);
}

void	create_philos(t_philo **first, int num_of_philos)
{
	t_philo	*aux;
	int		i;

	i = 1;
	(*first) = new_thread(NULL, i++);
	aux = (*first);
	while (i <= num_of_philos)
	{
		aux->next = new_thread(aux, i);
		aux = aux->next;
		++i;
	}
	(*first)->prev = aux;
	aux->next = (*first);
}

void	*print_status(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (!(philos->flags & DEAD))
	{
		if (philos->flags & FORK)
			printf("%i has taken a fork\n", philos->num_philo);
		if (philos->flags & EAT)
			printf("%i is eating\n", philos->num_philo);
		if (philos->flags & SLEEP)
			printf("%i is sleaping\n", philos->num_philo);
		if (philos->flags & THINK)
			printf("%i is thinking\n", philos->num_philo);
		philos = philos->next;
	}
	if (philos->flags & DEAD)
		printf("%i is dead\n", philos->num_philo);
	return (0);
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
		pthread_join(msg, NULL);
	}
	else
		return (ft_error(argv[1]));
	return (0);
}
