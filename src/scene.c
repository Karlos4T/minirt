/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:37:33 by carlosga          #+#    #+#             */
/*   Updated: 2024/03/15 16:58:38 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_scene	*initialize_scene()
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	scene->camera = start_camera(0, 0, 0, 0, 0, -1, 90);
	scene->alight = create_alight(0.3, 0x00FFFFFF);
	scene->lights = create_light(200, 150, -200, 1, 0x00FFFFFF);
	scene->objects = malloc(sizeof(t_objects));
	scene->objects->cylinders = malloc(sizeof(t_cylinder) * 2);
	scene->objects->cylinders[0] = create_cylinder(0, 0, -400, 1, 1, 0, 100, 200, 0x0000FFFF);
	scene->objects->cylinders[1] = NULL;
	scene->objects->spheres = malloc(sizeof(t_sphere) * 5);
	scene->objects->spheres[0] = create_sphere(-30, -30, -400, 40, 0x00AAAAAA);
	scene->objects->spheres[1] = create_sphere(0, 0, -400, 50, 0x00AA0000);
	scene->objects->spheres[2] = create_sphere(-30, 100, -400, 17, 0x0000AA00);
	scene->objects->spheres[3] = create_sphere(30, -30, -400, 20, 0x000000AA);
	scene->objects->spheres[4] = NULL;
	scene->objects->planes = malloc(sizeof(t_plane) * 3);
	scene->objects->planes[0] = create_plane(0, -500, 0, 0, 1, 0, 0x00880088);
	scene->objects->planes[1] = create_plane(0, 0, -3000, 0, 0, 1, 0x00177717);
	scene->objects->planes[2] = create_plane(-300, 0, 0, 1, 0, 0, 0x00007727);
	scene->objects->planes[0] = NULL;

	return scene;
}
