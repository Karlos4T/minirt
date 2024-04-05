/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:31:04 by carlosga          #+#    #+#             */
/*   Updated: 2024/04/05 13:01:16 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_ray *create_ray(t_camera *cam)
{
	t_ray *ray;

	ray = malloc(sizeof(t_ray));
	ray->o = cam->o;
	ray->v = cam->v;
	return ray;
}

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

t_vec *vec(double x, double y, double z)
{
	t_vec	*v;

	v = malloc(sizeof(t_vec));
	v->x = x;
	v->y = y;
	v->z = z;
	return (v);
}

t_vec	*create_vector(t_vec p1, t_vec p2)
{
	t_vec	*vector;

	vector = malloc(sizeof(t_vec));
	vector->x = p2.x - p1.x;
	vector->y = p2.y - p1.y;
	vector->z = p2.z - p1.z;
	return (vector);
}

t_vec	*create_point(int x, int y, int z)
{
	t_vec	*point;

	point = malloc(sizeof(t_vec));
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
