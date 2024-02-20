/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:31:04 by carlosga          #+#    #+#             */
/*   Updated: 2024/02/20 16:33:19 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_light *create_light(int x, int y, int z, double intensity, int color)
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

t_sphere *create_sphere(int x, int y, int z, int radius, int color)
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

t_vector *create_vector(t_cords point1, t_cords point2)
{
	t_vector *vector;

	vector = malloc(sizeof(t_vector));
	vector->x = point1.x + point2.x;
	vector->y = point1.y + point2.y;
	vector->z = point1.z + point2.z;
	return (vector);
}

t_cords *create_point(int x, int y, int z)
{
	t_cords *point;

	point = malloc(sizeof(t_cords));
	point->x = x;
	point->y = y;
	point->z = z;

	return (point);
}

t_camera *start_camera(int x, int y, int z, int fov)
{
	t_camera	*camera;
	t_cords		*cords;

	camera = malloc(sizeof(t_camera));
	cords = malloc(sizeof(t_cords));
	cords->x = x;
	cords->y = y;
	cords->z = z;
	camera->o = cords;
	camera->fov = fov;

	return camera;
}

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
