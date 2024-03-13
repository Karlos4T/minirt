/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:37:33 by carlosga          #+#    #+#             */
/*   Updated: 2024/03/13 16:56:56 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_scene	*initialize_scene()
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	scene->camera = start_camera(-200, 400, -200, 0.5, -1, -0.5, 90);
	scene->alight = create_alight(0.3, 0x00FFFFFF);
	scene->lights = create_light(-200, 400, -200, 1, 0x00FFFFFF);
	scene->objects = malloc(sizeof(t_objects));
	scene->objects->cylinders = malloc(sizeof(t_cylinder) * 2);
	scene->objects->cylinders[0] = create_cylinder(0, 0, -160, 1, 1, 0, 10, 70, 0x0000FFFF);
	scene->objects->cylinders[0] = NULL;
	scene->objects->spheres = malloc(sizeof(t_sphere) * 5);
	scene->objects->spheres[0] = create_sphere(-30, -30, -400, 12, 0x00AAAAAA);
	scene->objects->spheres[1] = create_sphere(30, 30, -400, 15, 0x00AA0000);
	scene->objects->spheres[2] = create_sphere(-30, 30, -400, 17, 0x0000AA00);
	scene->objects->spheres[3] = create_sphere(30, -30, -400, 20, 0x000000AA);
	scene->objects->spheres[1] = NULL;
	scene->objects->planes = malloc(sizeof(t_plane) * 3);
	scene->objects->planes[0] = create_plane(0, 0, -2500, 0, 0, -1, 0x00880088);
	scene->objects->planes[1] = create_plane(0, -300, -200, 0, 1, 0.1, 0x00177717);
	scene->objects->planes[2] = create_plane(300, 0, -400, -1, 0, 0.1, 0x00007727);
	scene->objects->planes[0] = NULL;

	return scene;
}
