/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:44:46 by carlosga          #+#    #+#             */
/*   Updated: 2024/02/27 16:10:47 by carlosga         ###   ########.fr       */
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

double vector_x_plane(t_plane pl, t_vector v)
{
	double t;

	t = (pl.v.x * pl.o.x + pl.v.y * pl.o.y + pl.v.z * pl.o.z) / (pl.v.x * v.x + pl.v.y * v.y + pl.v.z * v.z);
	return (t);
}

double get_brightness_level_plane(t_plane *pl, t_light *l, t_cords *p)
{
	t_vector	*v1;
	t_vector	v2;
	double		alpha;

	v1 = malloc(sizeof(t_vector));
	v1->x = pl->v.x + p->x;
	v1->y = pl->v.y + p->y;
	v1->z = pl->v.z + p->z;
	//printf("p: (%f, %f, %f)\n", p->x, p->y, p->z);
	v2 = *create_vector(l->o, *p);
	//alpha = (v1->x * v2.x + v1->y * v2.y + v1->z * v2.z)/* / (module(*v1) * module(v2))*/;
	//printf("alpha = %f\n", alpha);
	//alpha = (pow(alpha, 2) * (1 - module(v2) / 10000)) * l->intensity;
	alpha = pow(10 / sqrt(module(v2)), 4) * l->intensity;
	//if (module(v2) > 700)
	//printf("vector: (%f, %f, %f) modulev2 = %f\n", v2.x, v2.y, v2.z, module(v2));
	return (alpha);
}
