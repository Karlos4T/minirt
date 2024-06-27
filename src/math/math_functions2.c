/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:04:44 by dximenez          #+#    #+#             */
/*   Updated: 2024/06/27 14:05:57 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_vec	normalize(t_vec v)
{
	double	m;

	m = module(v);
	if (m == 0)
		m = 0.1;
	v.x = v.x / m;
	v.y = v.y / m;
	v.z = v.z / m;
	return (v);
}

t_vec	neg(t_vec v)
{
	v.x = -v.x;
	v.y = -v.y;
	v.z = -v.z;
	return (v);
}

t_vec	cross_prod(t_vec u, t_vec v)
{
	t_vec	dst;

	dst.x = u.y * v.z - u.z * v.y;
	dst.y = u.z * v.x - u.x * v.z;
	dst.z = u.x * v.y - u.y * v.x;
	return (dst);
}

t_vec	vec_add(t_vec v1, t_vec v2)
{
	v1.x = v1.x + v2.x;
	v1.y = v1.y + v2.y;
	v1.z = v1.z + v2.z;
	return (v1);
}

t_vec	vec_sub(t_vec v1, t_vec v2)
{
	t_vec	v;

	v.x = v2.x - v1.x;
	v.y = v2.y - v1.y;
	v.z = v2.z - v1.z;
	return (v);
}
