/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:51:28 by akdovlet          #+#    #+#             */
/*   Updated: 2024/12/07 18:17:16 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating_sequence(t_philo *philo)
{
	if (philo->id == philo->data->philo_count || !(philo->fork_right_mutex))
		pthread_mutex_lock(&philo->fork_left_mutex);
	else if (philo->fork_right_mutex)
		pthread_mutex_lock(philo->fork_right_mutex);
		
	pthread_mutex_lock(&philo->lock->write_mutex);
	printf("%-4ld ms philosopher %d has taken a fork\n", gettime_interval(&philo->data->time), philo->id);
	pthread_mutex_unlock(&philo->lock->write_mutex);
	
	if (philo->id == philo->data->philo_count && (philo->fork_right_mutex))
		pthread_mutex_lock(philo->fork_right_mutex);
	else if ((philo->fork_right_mutex))
		pthread_mutex_lock(&philo->fork_left_mutex);
	else
		return (pthread_mutex_unlock(&philo->fork_left_mutex), 0);

	pthread_mutex_lock(&philo->lock->write_mutex);
	printf("%-4ld ms philosopher %d has taken a fork\n", gettime_interval(&philo->data->time), philo->id);
	printf("%-4ld ms philosopher %d is eating\n", gettime_interval(&philo->data->time), philo->id);
	pthread_mutex_unlock(&philo->lock->write_mutex);
	
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal_time = gettime_in_ms();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	usleep(philo->data->time_to_eat * 1000);
	if (philo->fork_right_mutex)
		pthread_mutex_unlock(philo->fork_right_mutex);
	pthread_mutex_unlock(&philo->fork_left_mutex);
	philo->meals_nb += 1;
	if (philo->meals_nb == philo->data->eat_count)
	{
		pthread_mutex_lock(&philo->lock->ate_mutex);
		philo->lock->ate_count += 1;
		pthread_mutex_unlock(&philo->lock->ate_mutex);
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

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	pthread_mutex_lock(&philo->lock->start_mutex);
	pthread_mutex_unlock(&philo->lock->start_mutex);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal_time = gettime_in_ms();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	while (1)
	{
		if (is_dead(philo))
			break ;
		if (eating_sequence(philo))
			break;
		if (is_dead(philo))
			break ;
		pthread_mutex_lock(&philo->lock->write_mutex);
		printf("%-4ld ms philosopher %d is sleeping\n", gettime_interval(&philo->data->time), philo->id);
		pthread_mutex_unlock(&philo->lock->write_mutex);
		usleep(philo->data->time_to_sleep * 1000);
		if (is_dead(philo))
			break ;
		pthread_mutex_lock(&philo->lock->write_mutex);
		printf("%-4ld ms philosopher %d is thinking\n", gettime_interval(&philo->data->time), philo->id);
		pthread_mutex_unlock(&philo->lock->write_mutex);
	}
	return (NULL);
}

time_t	hunger_time(time_t last)
{
	time_t			interval;
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	interval = ((curr_time.tv_sec * 1000LL) + (curr_time.tv_usec / 1000)) -
				last;
	return (interval);
	
}

void	*monitoring_routine(void *arg)
{
	int		i;
	t_philo *philo;

	philo = (t_philo *) arg;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&philo[i].lock->ate_mutex);
		if (philo[i].lock->ate_count == philo[i].data->philo_count)
		{
			pthread_mutex_lock(&philo[i].lock->write_mutex);
			printf("All philosophers finished eating\n");
			pthread_mutex_unlock(&philo[i].lock->write_mutex);
			pthread_mutex_unlock(&philo[i].lock->ate_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo[i].lock->ate_mutex);
		pthread_mutex_lock(&philo[i].last_meal_mutex);
		if (hunger_time(philo[i].last_meal_time) >= philo[i].data->time_to_die)
		{
			pthread_mutex_lock(&philo[i].lock->write_mutex);
			printf("%-4ld ms philosopher %d is dead\n", gettime_interval(&philo->data->time), philo->id);
			pthread_mutex_unlock(&philo[i].lock->write_mutex);
			pthread_mutex_lock(&philo[i].lock->end_mutex);
			philo[i].lock->end = 1;
			pthread_mutex_unlock(&philo[i].lock->end_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo[i].last_meal_mutex);
		if (philo[i].id == philo[i].data->philo_count)
			i = 0;
		else
			i++;
	}
	return (NULL);
}
