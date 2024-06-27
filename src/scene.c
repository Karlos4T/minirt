/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:00:02 by dximenez          #+#    #+#             */
/*   Updated: 2024/06/27 14:03:51 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_vec	*vec(double x, double y, double z)
{
	t_vec	*v;

	v = malloc(sizeof(t_vec));
	v->x = x;
	v->y = y;
	v->z = z;
	return (v);
}

t_vec	vec_s(double x, double y, double z)
{
	t_vec	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}
