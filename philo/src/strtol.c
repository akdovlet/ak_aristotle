/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:05:53 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/21 18:06:57 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ak_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ak_strtol(const char *restrict nptr, char **restrict endptr, int base)
{
	char	*base;

	base = "0123456789abcdefghijklmnopqrstuvwxyz";
	base = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";		
}
