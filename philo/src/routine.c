/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:13:14 by akdovlet          #+#    #+#             */
/*   Updated: 2024/12/12 17:57:58 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal_time = gettime_in_ms();
	pthread_mutex_unlock(&philo->last_meal_mutex);
}

void	barrier_wait(pthread_mutex_t *barrier)
{
	pthread_mutex_lock(barrier);
	pthread_mutex_unlock(barrier);
}

void	update_meal_count(t_philo *philo)
{
	philo->meals_count += 1;
	if (philo->meals_count == philo->data->eat_count)
	{
		philo->meals_count++;
		pthread_mutex_lock(&philo->lock->ate_mutex);
		philo->lock->ate_count += 1;
		pthread_mutex_unlock(&philo->lock->ate_mutex);
	}
}

int	usleep_loop(t_philo *philo, int time)
{
	int	start;

	start = 0;
	while (start < time)
	{
		if (start + 50 > time)
			start = time - start;
		else
			start += 50;
		usleep(start * 1000);
		if (is_dead(philo))
			return (1);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	update_meal_time(philo);
	barrier_wait(&philo->lock->barrier);
	while (1)
	{
		if (eating_sequence(philo))
			break ;
		if (is_sleeping(philo))
			break ;
		if (usleep_loop(philo, philo->data->time_to_sleep))
			break ;
		usleep(philo->data->time_to_sleep * 1000);
		if (is_thinking(philo))
			break ;
	}
	return (NULL);
}
