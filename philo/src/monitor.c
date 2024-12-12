/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:30:28 by akdovlet          #+#    #+#             */
/*   Updated: 2024/12/12 17:50:36 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	hunger_time(time_t last)
{
	time_t			interval;
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	interval = ((curr_time.tv_sec * 1000LL) + (curr_time.tv_usec / 1000)) -
				last;
	return (interval);
	
}

static int	someone_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->state_mutex);
	if (philo->state == EATING)
	{
		pthread_mutex_unlock(&philo->state_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->state_mutex);
	pthread_mutex_lock(&philo->last_meal_mutex);
	if (hunger_time(philo->last_meal_time) >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->lock->end_mutex);
		philo->lock->end = 1;
		pthread_mutex_unlock(&philo->lock->end_mutex);
		pthread_mutex_lock(&philo->lock->write_mutex);
		printf("%8ld %d is dead\n", gettime_interval(&philo->data->time), philo->id);
		pthread_mutex_unlock(&philo->lock->write_mutex);
		pthread_mutex_unlock(&philo->last_meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (0);
}

static int	finished_eating(t_philo *philo)
{
	if (!philo->data->eat_count)
		return (0);
	pthread_mutex_lock(&philo->lock->ate_mutex);
	if (philo->lock->ate_count >= philo->data->philo_count)
	{
		pthread_mutex_lock(&philo->lock->write_mutex);
		printf("%8ld all philosophers finished eating\n", gettime_interval(&philo->data->time));
		pthread_mutex_unlock(&philo->lock->write_mutex);
		pthread_mutex_unlock(&philo->lock->ate_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->lock->ate_mutex);
	return (0);
}

void	*monitoring_routine(void *arg)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo[i].lock->barrier);
	pthread_mutex_unlock(&philo[i].lock->barrier);
	while (1)
	{
		usleep(100);
		if (someone_died(&philo[i]))
			break ;
		if (finished_eating(&philo[i]))
			break ;
		if (philo[i].id == philo[i].data->philo_count)
			i = 0;
		else
			i++;
	}
	return (NULL);
}
