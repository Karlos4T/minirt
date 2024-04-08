/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:44:46 by carlosga          #+#    #+#             */
/*   Updated: 2024/04/08 16:58:15 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_plane *create_plane(int x, int y, int z, double vx, double vy, double vz, int color)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	plane->o.x = x;
	plane->o.y = y;
	plane->o.z = z;
	plane->v.x = vx;
	plane->v.y = vy;
	plane->v.z = vz;
	plane->color = rgb(color);
	return (plane);
}

double vector_x_plane(t_plane pl, t_ray r)
{
	double t;
	double d;
	t_vec	v;

	v = r.v;
	d = dot_prod(pl.v, r.v);
	if (!d)
		return (0);
	t = -((pl.v.x * pl.o.x + pl.v.y * pl.o.y + pl.v.z * pl.o.z) - (pl.v.x * r.o.x + pl.v.y * r.o.y + pl.v.z * r.o.z)) / (pl.v.x * v.x + pl.v.y * v.y + v.z * pl.v.z);
	return (t);
}
