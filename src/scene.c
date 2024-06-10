/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:37:33 by carlosga          #+#    #+#             */
/*   Updated: 2024/06/09 22:01:45 by dximenez         ###   ########.fr       */
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
	scene->cam = create_camera(c_vec(0, 100, 0), c_vec(0, 0, -1), 90);
	scene->amb = create_alight(0.3, 0x00FFFFFF);
	scene->light = create_light(c_vec(500, 0, 500), 1, 0x00FFFFFF);


	scene->obj = malloc(sizeof(t_objects));

	scene->obj->n_cyl = 4;
	t_cylinder_p cy1 = {c_vec(0, 0, -400), c_vec(-1, 0, 1), 40, 100, 0x0000FFFF};
	scene->obj->cyl[0] = create_cylinder(cy1);

	t_cylinder_p cy2 = {c_vec(0, 200, -400), c_vec(0, 1, -1), 40, 80, 0x0000FFFF};
	scene->obj->cyl[1] = create_cylinder(cy2);

	t_cylinder_p cy3 = {c_vec(200, 200, -400), c_vec(0, 1, 0), 100, 100, 0x0000FFFF};
	scene->obj->cyl[2] = create_cylinder(cy3);

	t_cylinder_p cy4 = {c_vec(-50, 50, -400), c_vec(1, 1, 0), 40, 40, 0x0000FFFF};
	scene->obj->cyl[3] = create_cylinder(cy4);
	scene->obj->cyl[4] = NULL;

	scene->obj->n_sph = 4;
	scene->obj->sph[0] = create_sphere(c_vec(-30, -30, -400), 20, 0x00AAAAAA);
	scene->obj->sph[1] = create_sphere(c_vec(30, -30, -400), 20, 0x00AA0000);
	scene->obj->sph[2] = create_sphere(c_vec(-30, 100, -400), 17, 0x0000AA00);
	scene->obj->sph[3] = create_sphere(c_vec(30, -30, -400), 20, 0x000000AA);
	scene->obj->sph[4] = NULL;

	scene->obj->n_pla = 3;
	scene->obj->pla[0] = create_plane(c_vec(0, -500, 0), c_vec(0, 1, 0), 0x00880088);
	scene->obj->pla[1] = create_plane(c_vec(0, 0, -800), c_vec(0, 0, 1), 0x00177717);
	scene->obj->pla[2] = create_plane(c_vec(-300, 0, 0), c_vec(1, 0, 0), 0x00007727);
	scene->obj->pla[3] = NULL;

	return scene;
}
