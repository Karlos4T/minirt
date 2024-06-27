/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:11:15 by dximenez          #+#    #+#             */
/*   Updated: 2024/06/27 14:12:58 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_cylinder	*create_cylinder(t_cylinder_p cylinder)
{
	t_cylinder	*cy;

	cy = malloc(sizeof(t_cylinder));
	cy->o = cylinder.o;
	cy->v = cylinder.v;
	cy->radius = cylinder.diameter / 2;
	cy->is_cover = 0;
	cy->r2 = cylinder.diameter * cylinder.diameter * map_value(module(cy->v));
	cy->height = cylinder.height;
	cy->covers[0] = create_cover(cy, cylinder.color, 0);
	cy->covers[1] = create_cover(cy, cylinder.color, 1);
	cy->color = rgb(cylinder.color);
	return (cy);
}
