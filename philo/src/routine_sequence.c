/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_sequence.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:57:10 by akdovlet          #+#    #+#             */
/*   Updated: 2024/12/13 17:48:11 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating_sequence(t_philo *philo)
{
	int	end;

	if (is_dead(philo))
		return (1);
	end = locking_sequence(philo);
	if (!end)
	{
		is_eating(philo);
		update_meal_time(philo);
		if (usleep_loop(philo, philo->data->time_to_eat))
		{
			unlocking_sequence(philo);
			return (1);
		}
		update_meal_count(philo);
		unlocking_sequence(philo);
	}
	else if (end == 1)
		return (1);
	return (0);
}

int	locking_sequence(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_right_mutex);
	if (is_strapped(philo))
		return (pthread_mutex_unlock(philo->fork_right_mutex), 1);
	if (philo->fork_left_mutex)
	{
		if (is_dead(philo))
		{
			pthread_mutex_unlock(philo->fork_right_mutex);
			return (1);
		}
		pthread_mutex_lock(philo->fork_left_mutex);
		if (is_strapped(philo))
			return (unlocking_sequence(philo), 1);
	}
	else
		return (pthread_mutex_unlock(philo->fork_right_mutex), 2);
	return (0);
}

void	unlocking_sequence(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_right_mutex);
	if (philo->fork_left_mutex)
		pthread_mutex_unlock(philo->fork_left_mutex);
}
