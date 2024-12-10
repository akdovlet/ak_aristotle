/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:13:14 by akdovlet          #+#    #+#             */
/*   Updated: 2024/12/10 18:59:56 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock->write_mutex);
	printf("%-5ld ms philosopher %d is thinking\n", gettime_interval(&philo->data->time), philo->id);
	pthread_mutex_unlock(&philo->lock->write_mutex);
}

void	is_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock->write_mutex);
	printf("%-5ld ms philosopher %d is sleeping\n", gettime_interval(&philo->data->time), philo->id);
	pthread_mutex_unlock(&philo->lock->write_mutex);
}

void	is_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal_time = gettime_in_ms();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	pthread_mutex_lock(&philo->lock->write_mutex);
	printf("%-5ld ms philosopher %d is eating\n", gettime_interval(&philo->data->time), philo->id);
	pthread_mutex_unlock(&philo->lock->write_mutex);	
}

void	is_strapped(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock->write_mutex);
	printf("%-5ld ms philosopher %d has picked up a fork\n", gettime_interval(&philo->data->time), philo->id);
	pthread_mutex_unlock(&philo->lock->write_mutex);
}

int	locking_sequence(t_philo *philo)
{
	if (is_dead(philo))
		return (2);
	pthread_mutex_lock(philo->fork_right_mutex);
	if (is_dead(philo))
		return (pthread_mutex_unlock(philo->fork_right_mutex), 2);
	is_strapped(philo);
	if (philo->fork_left_mutex)
	{
		if (is_dead(philo))
			return (2);
		pthread_mutex_lock(philo->fork_left_mutex);
		is_strapped(philo);
		return (0);
	}
	return (1);
}

void	unlocking_sequence(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_right_mutex);
	if (philo->fork_left_mutex)
		pthread_mutex_unlock(philo->fork_left_mutex);
}

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

void	finished_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock->write_mutex);
	printf("%-5ld ms philosopher %d has finished eating\n", gettime_interval(&philo->data->time), philo->id);
	pthread_mutex_unlock(&philo->lock->write_mutex);
}

int	update_meal_count(t_philo *philo)
{
	philo->meals_nb += 1;
	if (philo->meals_nb == philo->data->eat_count)
	{
		pthread_mutex_lock(&philo->lock->ate_mutex);
		philo->lock->ate_count += 1;
		pthread_mutex_unlock(&philo->lock->ate_mutex);
		finished_eating(philo);
		return (1);	
	}
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

void	*routine_2(void *arg)
{
	t_philo	*philo;
	int		end;

	end = 0;
	philo = (t_philo *) arg;
	barrier_wait(&philo->lock->start_mutex);
	update_meal_time(philo);
	while (1)
	{
		if (is_dead(philo))
			break ;
		if (!locking_sequence(philo))
		{
			update_meal_time(philo);
			is_eating(philo);
			usleep(philo->data->time_to_eat * 1000);
			end = update_meal_count(philo);
		}
		unlocking_sequence(philo);
		if (end)
			break ;
		is_sleeping(philo);
		usleep(philo->data->time_to_sleep * 1000);
		is_thinking(philo);
	}
	return (NULL);
}
