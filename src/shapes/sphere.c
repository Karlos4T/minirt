/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:16:53 by carlosga          #+#    #+#             */
/*   Updated: 2024/04/06 14:00:54 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_sphere	*create_sphere(int x, int y, int z, int radius, int color)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	sphere->o.x = x;
	sphere->o.y = y;
	sphere->o.z = z;
	sphere->radius = radius;
	sphere->color = rgb(color);

	return sphere;
}

double	vector_x_sphere(t_sphere s, t_ray r)
{
	double	a;
	double	b;
	double	c;
	
	//v = normalize(v);
	a = dot_prod(r.v, r.v);
	b = 2 * (r.v.x * (r.o.x - s.o.x) + r.v.y * (r.o.y - s.o.y) + r.v.z * (r.o.z - s.o.z));
	c = pow(r.o.x - s.o.x, 2) + pow(r.o.y - s.o.y, 2) + pow(r.o.z - s.o.z, 2) - pow(s.radius, 2);
	
	return (quadratic(a, b, c));
}




