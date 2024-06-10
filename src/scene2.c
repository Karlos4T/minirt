/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:31:04 by carlosga          #+#    #+#             */
/*   Updated: 2024/06/08 16:28:13 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_light	*create_light(t_vec o, double intensity, int color)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	light->o = o;
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

t_vec	*vec(double x, double y, double z)
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

t_camera	*create_camera(t_vec o, t_vec v, int fov)
{
	t_camera	*camera;

	camera = malloc(sizeof(t_camera));
	camera->o = o;
	camera->v = v;
	camera->fov = fov;

	return (camera);
}
