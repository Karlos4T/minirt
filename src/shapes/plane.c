/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:44:46 by carlosga          #+#    #+#             */
/*   Updated: 2024/06/09 22:17:49 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_plane	*create_plane(t_vec o, t_vec v, int color)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	plane->o = o;
	plane->v = v;
	plane->color = rgb(color);
	return (plane);
}

double	vector_x_plane(t_plane *pl, t_ray r)
{
	double	t;
	double	d;
	t_vec	v;

	v = r.v;
	d = dot_prod(pl->v, r.v);
	if (!d)
		return (0);
	t = -((pl->v.x * pl->o.x + pl->v.y * pl->o.y + pl->v.z * pl->o.z)
			- (pl->v.x * r.o.x + pl->v.y * r.o.y + pl->v.z * r.o.z))
		/ (pl->v.x * v.x + pl->v.y * v.y + v.z * pl->v.z);
	return (t);
}
