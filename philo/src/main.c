/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:46:44 by akdovlet          #+#    #+#             */
/*   Updated: 2024/12/15 16:28:09 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pthread_join_all(t_philo *philo, int philo_count)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data			data;
	t_lock			lock;
	pthread_t		monitor;
	t_philo			*philo;

	if (setup_data(av, ac, &data, &lock))
		return (1);
	pthread_mutex_lock(&lock.barrier);
	philo = setup_philosophers(&data, &lock);
	if (!philo)
	{
		pthread_mutex_unlock(&lock.barrier);
		return (destroy_locks(&lock), 1);
	}
	pthread_create(&monitor, NULL, &monitoring_routine, philo);
	pthread_mutex_unlock(&lock.barrier);
	pthread_join_all(philo, data.philo_count);
	pthread_join(monitor, NULL);
	destroy_philo_mutex(philo, data.philo_count);
	return (0);
}
