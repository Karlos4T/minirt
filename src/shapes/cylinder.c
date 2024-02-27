/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:18:32 by carlosga          #+#    #+#             */
/*   Updated: 2024/02/27 13:31:38 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_cylinder  *create_cylinder(int x, int y, int z, double vx, double vy, double vz, double radius, double height, int color)
{
	t_cylinder	*cy;

	cy = malloc(sizeof(t_plane));
	cy->o.x = x;
	cy->o.y = y;
	cy->o.z = z;
	cy->v.x = vx;
	cy->v.y = vy;
	cy->v.z = vz;
    cy->radius = radius;
    cy->height = height;
	cy->color = rgb(color);
	return (cy);
}

double  vector_x_cylinder(t_cylinder cy, t_vector v)
{
    t = 1;
    return (t);
}