/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:18:13 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/21 17:28:22 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*table_new(int n)
{
	t_table	*new;

	new = malloc(sizeof(t_table));
	if (!new)
		return (NULL);
	new->philo_number = n;
	*new = (t_table){};
	return (new);
}

void	table_addback(t_table **first, t_table **last, t_table *new)
{
	if (!*last)
	{
		*last = new;
		*first = new;
		return ;
	}
	(*last)->next = new;
	new->prev = *last;
	*last = new;
}
