/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:23:07 by akdovlet          #+#    #+#             */
/*   Updated: 2024/12/15 15:48:25 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	link_data(t_philo *philo, t_data *data, t_lock *lock, int i)
{
	philo->id = i + 1;
	philo->data = data;
	philo->lock = lock;
	philo->last_meal_time = data->time;
}
