/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atol.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:05:53 by akdovlet          #+#    #+#             */
/*   Updated: 2024/12/15 17:25:33 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <unistd.h>
#include "philo.h"

int	ak_isnum(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ak_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

long	ak_atol(const char *restrict str, int *err)
{
	long	nb;
	long	flip;
	int		i;

	i = 0;
	nb = 0;
	flip = 1;
	while (str[i] && ak_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			return (write(2, "philo: negative value\n", 23), *err = 1, 1);
	while (str[i])
	{
		if (!ak_isnum(str[i]))
			return (*err = 1, \
			write(2, "philo: non numerical value\n", 28), -1);
		nb = (nb * 10) + (str[i++] - '0');
		if (nb * flip > INT_MAX || nb * flip < INT_MIN)
		{
			write(STDERR_FILENO, "philo: int overflow\n", 21);
			return (*err = 1, -1);
		}
	}
	return (nb * flip);
}
