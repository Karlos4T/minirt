/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:44:53 by carlosga          #+#    #+#             */
/*   Updated: 2024/06/27 14:04:38 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

int	x_pos(int x)
{
	return (x + WIN_WIDTH / 2 - WIN_WIDTH);
}

int	y_pos(int y)
{
	return (-y - WIN_HEIGHT / 2 + WIN_HEIGHT);
}

double	module(t_vec v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec	get_point(t_ray r, int t)
{
	t_vec	v;

	v.x = r.o.x + r.v.x * t;
	v.y = r.o.y + r.v.y * t;
	v.z = r.o.z + r.v.z * t;
	return (v);
}

t_vec	producto_escalar(t_vec v, double n)
{
	v.x = v.x * n;
	v.y = v.y * n;
	v.z = v.z * n;
	return (v);
}
