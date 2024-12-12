/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:46:44 by akdovlet          #+#    #+#             */
/*   Updated: 2024/12/10 22:34:50 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*setup_philosophers(t_data *data, t_lock *lock)
{
	t_philo	*dinner;
	int		i;

	i = 0;
	dinner = malloc(sizeof(t_philo) * data->philo_count);
	if (!dinner)
		return (perror("philo: fatal error: setup philosophers"), NULL);
	while (i < data->philo_count)
	{
		dinner[i] = (t_philo) {};
		if (i < data->philo_count - 1)
		{
			dinner[i].fork_left_mutex = &dinner[i].fork_left;
			dinner[i].fork_right_mutex = &dinner[i + 1].fork_left;
			pthread_mutex_init(&dinner[i].fork_left, NULL);
		}
		else
		{
			if (data->philo_count > 1)
				dinner[i].fork_left_mutex = &dinner[0].fork_left;
			dinner[i].fork_right_mutex = &dinner[i].fork_left;
			pthread_mutex_init(dinner[i].fork_right_mutex, NULL);
		}
		pthread_mutex_init(&dinner[i].dead_mutex, NULL);
		pthread_mutex_init(&dinner[i].meals_count_mutex, NULL);
		pthread_mutex_init(&dinner[i].last_meal_mutex, NULL);
		dinner[i].id = i + 1;
		dinner[i].data = data;
		dinner[i].lock = lock;
		pthread_create(&dinner[i].thread, NULL, &routine_2, &dinner[i]);
		i++;
	}
	return (dinner);
}

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
	gettimeofday(&data.time, NULL);
	pthread_mutex_unlock(&lock.barrier);
	pthread_create(&monitor, NULL, &monitoring_routine, philo);
	pthread_join_all(philo, data.philo_count);
	pthread_join(monitor, NULL);
	destroy_philo_mutex(philo, data.philo_count);
	return (0);
}
