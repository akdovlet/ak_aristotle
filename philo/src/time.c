/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:47:38 by akdovlet          #+#    #+#             */
/*   Updated: 2024/12/15 16:33:31 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

double	convert_miliseconds(time_t sec, time_t usec)
{
	double	time_ms;

	time_ms = sec * 1000LL + usec / 1000LL;
	return (time_ms);
}

double	gettime_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (convert_miliseconds(time.tv_sec, time.tv_usec));
}

time_t	gettime_interval(time_t start)
{
	struct timeval	current_time;
	time_t			interval;

	gettimeofday(&current_time, NULL);
	interval = ((current_time.tv_sec * 1000LL) + \
				(current_time.tv_usec / 1000)) - start;
	return (interval);
}
