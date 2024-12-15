/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:53:40 by akdovlet          #+#    #+#             */
/*   Updated: 2024/12/15 16:41:03 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock->write_mutex);
	pthread_mutex_lock(&philo->lock->end_mutex);
	if (philo->lock->end)
	{
		pthread_mutex_unlock(&philo->lock->write_mutex);
		pthread_mutex_unlock(&philo->lock->end_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->lock->end_mutex);
	printf("%ld %d is thinking\n", gettime_interval(philo->data->time),
		philo->id);
	pthread_mutex_unlock(&philo->lock->write_mutex);
	if (usleep_loop(philo, philo->data->time_to_think))
		return (1);
	return (0);
}

int	is_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock->write_mutex);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->lock->write_mutex);
		return (1);
	}
	printf("%ld %d is sleeping\n", gettime_interval(philo->data->time),
		philo->id);
	pthread_mutex_unlock(&philo->lock->write_mutex);
	if (usleep_loop(philo, philo->data->time_to_sleep))
		return (1);
	return (0);
}

int	is_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock->write_mutex);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->lock->write_mutex);
		return (1);
	}
	printf("%ld %d is eating\n", gettime_interval(philo->data->time),
		philo->id);
	pthread_mutex_unlock(&philo->lock->write_mutex);
	return (0);
}

int	is_strapped(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock->write_mutex);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->lock->write_mutex);
		return (1);
	}
	printf("%ld %d has taken a fork\n", gettime_interval(philo->data->time),
		philo->id);
	pthread_mutex_unlock(&philo->lock->write_mutex);
	return (0);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock->end_mutex);
	if (philo->lock->end)
	{
		pthread_mutex_unlock(&philo->lock->end_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->lock->end_mutex);
	return (0);
}
