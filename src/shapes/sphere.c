/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:16:53 by carlosga          #+#    #+#             */
/*   Updated: 2024/03/15 13:22:08 by carlosga         ###   ########.fr       */
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

double	vector_x_sphere(t_sphere s, t_vec v, t_vec vo)
{
	double	a;
	double	b;
	double	c;
	
	//v = normalize(v);
	a = dot_prod(v, v);
	b = 2 * (v.x * (vo.x - s.o.x) + v.y * (vo.y - s.o.y) + v.z * (vo.z - s.o.z));
	c = pow(vo.x - s.o.x, 2) + pow(vo.y - s.o.y, 2) + pow(vo.z - s.o.z, 2) - pow(s.radius, 2);
	
	return (quadratic(a, b, c));
}




