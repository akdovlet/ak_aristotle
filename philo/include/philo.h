/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:47:52 by akdovlet          #+#    #+#             */
/*   Updated: 2024/12/12 18:15:43 by akdovlet         ###   ########.fr       */
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

typedef enum e_state
{
	THINKING,
	SLEEPING,
	EATING
}	t_state;

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	struct timeval	time;
}	t_data;

typedef struct	s_locks
{
	int				ate_count;
	int				end;
	pthread_mutex_t	ate_mutex;
	pthread_mutex_t	barrier;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	end_mutex;
}	t_lock;

typedef struct s_philo
{
	int				id;
	int				meals_count;
	t_state			state;
	time_t			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	meals_count_mutex;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	fork_left;
	pthread_mutex_t	*fork_left_mutex;
	pthread_mutex_t	*fork_right_mutex;
	t_lock			*lock;
	t_data			*data;
}	t_philo;

long	ak_atol(const char *restrict str, int *err);

/* setup.c */

int	setup_data(char **av, int ac, t_data *data, t_lock *locks);

/* time.c */

time_t	gettime_interval(struct timeval *start);
double	gettime_in_ms(void);

/* clear.c */

void			destroy_locks(t_lock *locks);
void			destroy_philo_mutex(t_philo *philo, int philo_count);
struct timeval	gettime_val(void);

/* routine.c */

void	*monitoring_routine(void *arg);
int		is_dead(t_philo *philo);

/* routine.c */

void	*routine(void *arg);
int		usleep_loop(t_philo *philo, int time);

/* monitor.c */

void	*monitoring_routine(void *arg);
void	update_meal_time(t_philo *philo);
void	update_meal_count(t_philo *philo);

/* routine_state.c */

int		is_thinking(t_philo *philo);
int		is_sleeping(t_philo *philo);
int		is_eating(t_philo *philo);
int		is_strapped(t_philo *philo);
int		is_dead(t_philo *philo);

/* routine_sequence.c */

int		eating_sequence(t_philo *philo);
int		locking_sequence(t_philo *philo);
void	unlocking_sequence(t_philo *philo);

#endif
