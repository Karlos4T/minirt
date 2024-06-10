/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:53:31 by dximenez          #+#    #+#             */
/*   Updated: 2024/06/08 14:53:38 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

static int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

double	ft_atod(char *s)
{
	long	num;
	double	dec;
	double	power;
	int		sign;

	num = 0;
	dec = 0;
	power = 0.1;
	sign = 1;
	while (is_space(*s))
		++s;
	if (*s == '+' || *s == '-')
		if (*s++ == '-')
			sign = -1;
	while (*s != '.' && *s != '\0' && *s >= '0' && *s <= '9')
		num = num * 10 + (*s++ - '0');
	if (*s == '.')
		++s;
	while (*s != '\0' && *s >= '0' && *s <= '9')
	{
		dec = dec + (*s++ - '0') * power;
		power /= 10;
	}
	return ((num + dec) * sign);
}
