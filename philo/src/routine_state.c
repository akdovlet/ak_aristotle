/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:53:40 by akdovlet          #+#    #+#             */
/*   Updated: 2024/12/12 18:26:28 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->state_mutex);
	philo->state = THINKING;
	pthread_mutex_unlock(&philo->state_mutex);
	pthread_mutex_lock(&philo->lock->write_mutex);
	pthread_mutex_lock(&philo->lock->end_mutex);
	if (philo->lock->end)
	{
		pthread_mutex_unlock(&philo->lock->write_mutex);
		pthread_mutex_unlock(&philo->lock->end_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->lock->end_mutex);
	printf("%8ld %d is thinking\n", gettime_interval(&philo->data->time), philo->id);
	pthread_mutex_unlock(&philo->lock->write_mutex);
	return (0);
}

int	is_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->state_mutex);
	philo->state = SLEEPING;
	pthread_mutex_unlock(&philo->state_mutex);
	pthread_mutex_lock(&philo->lock->write_mutex);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->lock->write_mutex);
		return (1);
	}
	printf("%8ld %d is sleeping\n", gettime_interval(&philo->data->time), philo->id);
	pthread_mutex_unlock(&philo->lock->write_mutex);
	return (0);
}

int	is_eating(t_philo *philo)
{
	update_meal_time(philo);
	pthread_mutex_lock(&philo->state_mutex);
	philo->state = EATING;
	pthread_mutex_unlock(&philo->state_mutex);
	pthread_mutex_lock(&philo->lock->write_mutex);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->lock->write_mutex);	
		return (1);
	}
	printf("%8ld %d is eating\n", gettime_interval(&philo->data->time), philo->id);
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
	printf("%8ld %d has picked up a fork\n", gettime_interval(&philo->data->time), philo->id);
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
