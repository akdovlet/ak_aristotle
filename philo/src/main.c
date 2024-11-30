/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:46:44 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/30 16:21:19 by akdovlet         ###   ########.fr       */
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

double	convert_miliseconds(time_t sec, time_t usec)
{
	double	time_ms;

	time_ms = sec * 1000LL + usec / 1000LL;
	return (time_ms);
}

double	gettime_in_ms(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (convert_miliseconds(time.tv_sec, time.tv_usec));
}


time_t	gettime_interval(struct timeval start, struct timeval end)
{
	return ((end.tv_sec * 1000000 + end.tv_usec) - 
	(start.tv_sec * 1000000 + start.tv_usec));
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	pthread_mutex_lock(philo->start);
	pthread_mutex_unlock(philo->start);
	pthread_mutex_lock(&philo->fork_left);
	printf("%.f ms philosopher %d has taken a fork\n", gettime_in_ms(), philo->id);
	pthread_mutex_lock(&philo->fork_right);
	printf("%.f ms philosopher %d has taken a fork\n", gettime_in_ms(), philo->id);
	pthread_mutex_unlock(&philo->fork_left);
	pthread_mutex_unlock(&philo->fork_right);
	return (NULL);
}

t_philo	*setup_philosophers(t_data *data, t_lock *lock)
{
	t_philo	*dinner;
	size_t		i;

	i = 0;
	dinner = malloc(sizeof(t_philo) * data->philo_count);
	if (!dinner)
		return (perror("philo: fatal: setup philosophers"), NULL);
	while (i < data->philo_count)
	{
		if (i < data->philo_count - 1)
			dinner[i].fork_right = dinner[i + 1].fork_left;
		else
			dinner[i].fork_right = dinner[0].fork_left;
		pthread_mutex_init(&dinner[i].fork_left, NULL);
		pthread_mutex_init(&dinner[i].dead, NULL);
		pthread_mutex_init(&dinner[i].meals_count, NULL);
		dinner[i].id = i;
		dinner[i].start = &lock->start;
		dinner[i].data = data;
		pthread_create(&dinner[i].thread, NULL, &routine, &dinner[i]);
		i++;
	}
	return (dinner);
}

int	setup_locks(t_lock *locks)
{
	*locks = (t_lock){};
	pthread_mutex_init(&locks->end, NULL);
	pthread_mutex_init(&locks->start, NULL);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;
	t_lock	lock;
	struct timeval	end;

	data = (t_data){};
	setup_locks(&lock);
	fprintf(stderr, "Locked barrier\n");
	pthread_mutex_lock(&lock.start);
	if ((ac < 5 || ac > 6) || parse_values(av, ac, &data))
	{
		write(2, "Invalid arguments\n", 19);
		return (1);
	}
	philo = setup_philosophers(&data, &lock);
	if (!philo)
		return (1);
	gettimeofday(&data.time, NULL);
	fprintf(stderr, "Start time is %ld\n", data.time.tv_usec);
	pthread_mutex_unlock(&lock.start);
	gettimeofday(&end, NULL);
	fprintf(stderr, "Main thread: unlocked barrier\n");
	for (unsigned int i = 0; i < data.philo_count; i++)
		pthread_join(philo[i].thread, NULL);
	fprintf(stderr, "Code ran for: %ld miliseconds\n", end.tv_usec - data.time.tv_usec);
	return (0);
}
