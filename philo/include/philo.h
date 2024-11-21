/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:47:52 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/21 17:17:33 by akdovlet         ###   ########.fr       */
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

typedef struct s_table
{
	int	philo_number;
	struct s_table	*next;
	struct s_table	*prev;
}	t_table;

typedef struct s_data
{
	int	philo_count;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_count;
	t_table	*first;
	t_table	*last;
}	t_data;

#endif
