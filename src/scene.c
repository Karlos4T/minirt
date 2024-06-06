/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:37:33 by carlosga          #+#    #+#             */
/*   Updated: 2024/06/06 23:07:21 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static t_vec	c_vec(double x, double y, double z)
{
	t_vec	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_scene	*initialize_scene()
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	scene->camera = create_camera(c_vec(0, 100, 0), c_vec(0, 0, -1), 90);
	scene->alight = create_alight(0.3, 0x00FFFFFF);
	scene->lights = create_light(c_vec(500, 0, -700), 1, 0x00FFFFFF);


	scene->objects = malloc(sizeof(t_objects));

	scene->objects->cylinders = malloc(sizeof(t_cylinder) * 2);

	t_cylinder_p cy1 = {c_vec(0, 0, -400), c_vec(-1, 0, 1), 40, 100, 0x0000FFFF};
	scene->objects->cylinders[0] = create_cylinder(cy1);

	t_cylinder_p cy2 = {c_vec(0, 200, -400), c_vec(0, 1, -1), 40, 80, 0x0000FFFF};
	scene->objects->cylinders[1] = create_cylinder(cy2);

	t_cylinder_p cy3 = {c_vec(200, 200, -400), c_vec(0, 1, 0), 100, 100, 0x0000FFFF};
	scene->objects->cylinders[2] = create_cylinder(cy3);

	t_cylinder_p cy4 = {c_vec(-50, 50, -400), c_vec(1, 1, 0), 40, 40, 0x0000FFFF};
	scene->objects->cylinders[3] = create_cylinder(cy4);
	scene->objects->cylinders[4] = NULL;


	scene->objects->spheres = malloc(sizeof(t_sphere) * 5);
	scene->objects->spheres[0] = create_sphere(c_vec(-30, -30, -400), 20, 0x00AAAAAA);
	scene->objects->spheres[1] = create_sphere(c_vec(30, -30, -400), 20, 0x00AA0000);
	scene->objects->spheres[2] = create_sphere(c_vec(-30, 100, -400), 17, 0x0000AA00);
	scene->objects->spheres[3] = create_sphere(c_vec(30, -30, -400), 20, 0x000000AA);
	scene->objects->spheres[4] = NULL;


	scene->objects->planes = malloc(sizeof(t_plane) * 3);
	scene->objects->planes[0] = create_plane(c_vec(0, -500, 0), c_vec(0, 1, 0), 0x00880088);
	scene->objects->planes[1] = create_plane(c_vec(0, 0, -800), c_vec(0, 0, 1), 0x00177717);
	scene->objects->planes[2] = create_plane(c_vec(-300, 0, 0), c_vec(1, 0, 0), 0x00007727);
	scene->objects->planes[3] = NULL;

	return scene;
}
