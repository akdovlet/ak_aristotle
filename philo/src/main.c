/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:46:44 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/24 17:49:54 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_values(char **av, int ac, t_data *data)
{
	int	i;

	i = 0;
	data->philo_count = ak_atol(av[1], &i);
	data->time_to_die = ak_atol(av[2], &i);
	data->time_to_eat = ak_atol(av[3], &i);
	data->time_to_sleep = ak_atol(av[4], &i);
	if (ac > 5)
		data->eat_count = ak_atol(av[5], &i);
	return (i);
}

void	*routine(t_philo *philo)
{
	pthread_mutex_init()
}

t_philo	*setup_philosophers(t_data *data)
{
	t_philo	*dinner;
	int		i;

	i = 0;
	dinner = malloc(sizeof(t_philo) * data->philo_count);
	if (!dinner)
		return (perror("philo: fatal: setup philosophers"), NULL);
	while (i < data->philo_count)
	{
		pthread_mutex_init(&dinner[i].fork, NULL);
		pthread_mutex_init(&dinner[i].dead, NULL);
		pthread_mutex_init(&dinner[i].meals_count, NULL);
		pthread_create(&dinner[i].thread, NULL, (void (*)(void *)) routine, &dinner[i]);
		i++;
	}
	
}

int	setup_data(t_data *data)
{
	pthread_mutex_init(data->eat_count);
	pthread_mutex_init(data->start_time);	
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;

	data = (t_data){};
	if ((ac < 5 || ac > 6) || parse_values(av, ac, &data))
	{
		write(2, "Invalid arguments\n", 19);
		return (1);
	}
	setup_data(&data);
	philo = setup_philosopers(&data);
	if (!philo)
		return (1);
	return (0);
}
