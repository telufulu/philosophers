/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:45:52 by telufulu          #+#    #+#             */
/*   Updated: 2024/04/04 22:35:35 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*say_hi(void *arg)
{
	int	i;

	i = 10;
	usleep(1000000);
	while (--i)
		printf("Hi! I'm %p", arg);
	return (0);
}

t_philo	*new_thread(t_philo *philo)
{
	t_philo	*aux;

	aux = ft_calloc(sizeof(t_philo), 1);
	if (!aux)
		return (NULL);
	aux->prev = philo;
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

int	main(int argc, char **argv)
{
	t_philo	*philosophers;

	philosophers = NULL;
	if (argc == 5 || argc == 6)
	{
		create_philos(&philosophers, ft_atoi(argv[1]));
		if (!philosophers || !philosophers->prev)
			return (ft_error("Fallo al crear hilo"));
	}
	else
		return (ft_error(argv[1]));
	return (0);
}
