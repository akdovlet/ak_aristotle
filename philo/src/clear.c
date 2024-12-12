/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:51:13 by akdovlet          #+#    #+#             */
/*   Updated: 2024/12/10 22:34:50 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_locks(t_lock *locks)
{
	pthread_mutex_destroy(&locks->end_mutex);
	pthread_mutex_destroy(&locks->barrier);
	pthread_mutex_destroy(&locks->write_mutex);
}

void	destroy_philo_mutex(t_philo *philo, int philo_count)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		if (i + 1 == philo_count)
			pthread_mutex_destroy(philo[i].fork_right_mutex);
		else
			pthread_mutex_destroy(philo[i].fork_left_mutex);
		pthread_mutex_destroy(&philo[i].dead_mutex);
		pthread_mutex_destroy(&philo[i].last_meal_mutex);
		pthread_mutex_destroy(&philo[i].meals_count_mutex);
		i++;
	}
	free(philo);
}
