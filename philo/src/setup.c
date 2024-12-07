/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:21:58 by akdovlet          #+#    #+#             */
/*   Updated: 2024/12/07 16:42:42 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_values(char **av, int ac, t_data *data)
{
	int	i;

	i = 0;
	data->philo_count = ak_atol(av[1], &i);
	if (!data->philo_count)
		i = 1;
	data->time_to_die = ak_atol(av[2], &i);
	data->time_to_eat = ak_atol(av[3], &i);
	data->time_to_sleep = ak_atol(av[4], &i);
	if (ac > 5)
		data->eat_count = ak_atol(av[5], &i);
	return (i);
}

int	setup_locks(t_lock *locks)
{
	if (pthread_mutex_init(&locks->end_mutex, NULL))
		return (printf("philo: mutex init error\n"), 1);
	if (pthread_mutex_init(&locks->start_mutex, NULL))
	{
		pthread_mutex_destroy(&locks->end_mutex);
		return (printf("philo: mutex init error\n"), 1);
	}
	if (pthread_mutex_init(&locks->write_mutex, NULL))
	{
		pthread_mutex_destroy(&locks->end_mutex);
		pthread_mutex_destroy(&locks->start_mutex);
		return (printf("philo: mutex init error\n"), 1);
	}
	return (0);
}

int	setup_data(char **av, int ac, t_data *data, t_lock *locks)
{
	*data = (t_data){};
	*locks = (t_lock){};
	if (ac < 5 || ac > 6)
	{
		write(2, "Invalid arguments\n", 19);
		return (1);
	}
	if (parse_values(av, ac, data))
		return (1);
	if (setup_locks(locks))
		return (1);
	return (0);
}
