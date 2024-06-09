/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:16:53 by carlosga          #+#    #+#             */
/*   Updated: 2024/06/09 22:16:23 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_sphere	*create_sphere(t_vec v3, int diameter, int color)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	sphere->o = v3;
	sphere->diameter = diameter;
	sphere->color = rgb(color);
	return (sphere);
}

double	vector_x_sphere(t_sphere *s, t_ray r)
{
	double	a;
	double	b;
	double	c;

	//v = normalize(v);
	a = dot_prod(r.v, r.v);
	b = 2 * (r.v.x * (r.o.x - s->o.x)
			+ r.v.y * (r.o.y - s->o.y) + r.v.z * (r.o.z - s->o.z));
	c = pow(r.o.x - s->o.x, 2) + pow(r.o.y - s->o.y, 2)
		+ pow(r.o.z - s->o.z, 2) - pow(s->diameter, 2);
	return (quadratic(a, b, c));
}




