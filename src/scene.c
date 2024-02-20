/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:37:33 by carlosga          #+#    #+#             */
/*   Updated: 2024/02/20 16:45:19 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_scene *initialize_scene()
{
    t_scene *scene;

    scene = malloc(sizeof(t_scene));
    scene->camera = start_camera(0, 0, 0, 90);
    scene->lights = create_light(10, 100, -100, 0.5, 0x00FFFFFF);
    scene->objects = malloc(sizeof(t_objects));
    scene->objects->spheres = malloc(sizeof(t_sphere) * 5);
    scene->objects->spheres[0] = create_sphere(-30, -30, -150, 12, 0x00FFFFFF);
    scene->objects->spheres[1] = create_sphere(30, 30, -100, 15, 0x00FF0000);
    scene->objects->spheres[2] = create_sphere(-30, 30, -100, 17, 0x0000FF00);
    scene->objects->spheres[3] = create_sphere(30, -30, -100, 20, 0x000000FF);
    scene->objects->spheres[4] = NULL;
    scene->objects->planes = malloc(sizeof(t_plane) * 2);
    scene->objects->planes[0] = create_plane(0, 0, -200, 0, 1, -0.2, 0x00FFFFFF);
    scene->objects->planes[1] = NULL;
    
    return scene;
}
