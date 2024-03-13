/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:44:53 by carlosga          #+#    #+#             */
/*   Updated: 2024/03/13 13:30:51 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

int x_pos(int x)
{
    return (x + WIN_WIDTH / 2 - WIN_WIDTH);
}

int y_pos(int y)
{
    return (-y - WIN_HEIGHT / 2 + WIN_HEIGHT);
}

double module(t_vector v)
{
	return(sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vector producto_escalar(t_vector v, double n)
{
	v.x = v.x * n;
	v.y = v.y * n;
	v.z = v.z * n;
	return (v);
}

t_vector normalize(t_vector v)
{
	v.x = v.x / module(v);
	v.y = v.y / module(v);
	v.z = v.z / module(v);
	return(v);
}

t_vector neg(t_vector v)
{
	v.x = -v.x;
	v.y = -v.y;
	v.z = -v.z;
	return (v);
}


double dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_cords *get_screen_coord(int x, int y, t_camera *camera)
{
	t_cords	*coords;
	double	limit;
	
	limit = tan(camera->fov/2);	
	coords = malloc(sizeof(t_cords));
	coords->x = x * limit / 1080 + camera->o.x;
	coords->y = y * limit / 1080 + camera->o.y;
	coords->z = camera->o.z - 1;
	return(coords);
}
