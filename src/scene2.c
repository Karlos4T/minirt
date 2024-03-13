/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:31:04 by carlosga          #+#    #+#             */
/*   Updated: 2024/03/13 15:57:15 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_light	*create_light(int x, int y, int z, double intensity, int color)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	light->o.x = x;
	light->o.y = y;
	light->o.z = z;
	light->intensity = intensity;
	light->color = rgb(color);

	return (light);
}

t_alight	*create_alight(double intensity, int color)
{
	t_alight	*light;

	light = malloc(sizeof(t_alight));
	light->intensity = intensity;
	light->color = rgb(color);
	return (light);
}

t_vector	*create_vector(t_cords p1, t_cords p2)
{
	t_vector	*vector;

	vector = malloc(sizeof(t_vector));
	vector->x = p2.x - p1.x;
	vector->y = p2.y - p1.y;
	vector->z = p2.z - p1.z;
	return (vector);
}

t_cords	*create_point(int x, int y, int z)
{
	t_cords	*point;

	point = malloc(sizeof(t_cords));
	point->x = x;
	point->y = y;
	point->z = z;
	return (point);
}

t_camera	*start_camera(double x, double y, double z, double vx, double vy, double vz, int fov)
{
	t_camera	*camera;

	camera = malloc(sizeof(t_camera));
	camera->o.x = x;
	camera->o.y = y;
	camera->o.z = z;
	camera->v.x = vx;
	camera->v.y = vy;
	camera->v.z = vz;
	
	camera->fov = fov;

	return camera;
}
