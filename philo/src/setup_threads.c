/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 14:05:18 by akdovlet          #+#    #+#             */
/*   Updated: 2024/12/15 16:41:09 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	left_handed_philosopher(t_philo *socrates, t_philo *plato)
{
	socrates->fork_left_mutex = &plato->fork_left;
	socrates->fork_right_mutex = &socrates->fork_left;
	if (pthread_mutex_init(&socrates->fork_left, NULL))
		perror("philo: fatal error: left_handed_philosopher");
}

void	right_handed_philosopher(t_philo *socrates, t_philo *plato)
{
	socrates->fork_left_mutex = &socrates->fork_left;
	socrates->fork_right_mutex = &plato->fork_left;
	pthread_mutex_init(&socrates->fork_left, NULL);
}

void	last_philosopher(t_philo *socrates, t_philo *plato, int philo_count)
{
	socrates->fork_right_mutex = &plato->fork_left;
	if (philo_count > 1)
	{
		pthread_mutex_init(&socrates->fork_left, NULL);
		socrates->fork_left_mutex = &socrates->fork_left;
	}
	else
		pthread_mutex_init(&plato->fork_left, NULL);
}

void	dispatch_forks(t_philo *socrates, t_philo *plato, int i)
{
	if (i % 2)
		left_handed_philosopher(socrates, plato);
	else
		right_handed_philosopher(socrates, plato);
}

t_philo	*setup_philosophers(t_data *data, t_lock *lock)
{
	int		i;
	time_t	start;
	t_philo	*dinner;

	i = 0;
	dinner = malloc(sizeof(t_philo) * data->philo_count);
	if (!dinner)
		return (perror("philo: fatal error: setup_philosophers"), NULL);
	start = gettime_in_ms();
	data->time = start;
	while (i < data->philo_count)
	{
		dinner[i] = (t_philo){};
		if (i < data->philo_count - 1)
			dispatch_forks(&dinner[i], &dinner[i + 1], i);
		else
			last_philosopher(&dinner[i], &dinner[0], data->philo_count);
		pthread_mutex_init(&dinner[i].last_meal_mutex, NULL);
		link_data(&dinner[i], data, lock, i);
		pthread_create(&dinner[i].thread, NULL, &routine, &dinner[i]);
		i++;
	}
	return (dinner);
}
