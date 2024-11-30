/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:47:52 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/30 15:57:29 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h> // usleep, write
# include <string.h> // memset
# include <stdlib.h> // malloc, free
# include <sys/time.h> // gettimeofday
# include <pthread.h> 	// pthread_create, pthread_detach, pthread_join
// pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock
# include <stdio.h> // printf
# include <time.h>

typedef struct s_data
{
	unsigned int	philo_count;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	eat_count;
	struct timeval	time;
}	t_data;

typedef struct s_philo
{
	unsigned short	id;
	time_t			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	meals_count;
	pthread_mutex_t	dead;
	pthread_mutex_t	fork_left;
	pthread_mutex_t	fork_right;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	*start;
	t_data			*data;
}	t_philo;

typedef struct	s_locks
{
	pthread_mutex_t	start;
	pthread_mutex_t	write;
	pthread_mutex_t	end;
}	t_lock;

long	ak_atol(const char *restrict str, int *err);

#endif
