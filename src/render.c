/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:33:53 by carlosga          #+#    #+#             */
/*   Updated: 2024/04/04 13:48:05 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void render_pixel(int x, int y, t_data *data, t_scene sc)
{
	t_vec	*screen_point;
	t_vec	vector;
	int color = 0;
	double	t;
	double T[3];
	int i;
	double	alpha;

	T[0] = 0;
	T[1] = 0;
	screen_point = get_screen_coord(x_pos(x), y_pos(y), sc.camera);
	vector = vec_sub(sc.camera->o, *screen_point);
	//printf("v(%f, %f, %f)\n", vector->x, vector->y, vector->z);
	i = 0;
	while (sc.objects->planes[i] != NULL)
	{
		t = vector_x_plane(*sc.objects->planes[i], vector);
		//printf("t plane %i: %f --- ", i, t);
		//ULTIMA CONDICION TEMPORAL. SIN ELLA SE PRINTEA PARTE DEL PLANO POR ENCIMA PORQUE ENCUENTRA PUNTO DE CORTE POR DETRAS DE LA CAMARA
		if (t && (fabs(t) < fabs(T[0]) || !T[0]) && t < 0)
		{
			T[0] = fabs(t);
			T[1] = 1;
			T[2] = i;
		}
		i++;
	}
	//printf(" T: %f\n", T[0]);
	i = 0;
	while (sc.objects->spheres[i] != NULL)
	{
		t = vector_x_sphere(*sc.objects->spheres[i], vector, sc.camera->o);
		if (t && (fabs(t) < fabs(T[0]) || !T[0]))
		{
			T[0] = t;
			T[1] = 2;
			T[2] = i;
		}
		i++;
	}
	i = 0;
	while (sc.objects->cylinders[i] != NULL)
	{
		t = vector_x_cylinder(*sc.objects->cylinders[i], vector, sc.camera->o);
		if (t && (fabs(t) < fabs(T[0]) || !T[0]))
		{
			T[0] = t;
			T[1] = 3;
			T[2] = i;
		}
		i++;
	}
	if (T[1] == 1)
	{
		t_plane *pl = sc.objects->planes[(int)T[2]];
		t_vec *p;
		
		p = create_point(sc.camera->o.x + T[0] * vector.x,  sc.camera->o.y + T[0] * vector.y, sc.camera->o.z + T[0] * vector.z);
		//printf("v(%f, %f, %f)\n", p->x, p->y, p->z);
		
		alpha = get_brightness_level_plane(pl, sc.lights, p);

		color = (1 - check_shadow(*p, sc.lights[0].o, sc.objects->spheres)) * hexa(multiply_colors(pl->color, sc.lights->color, alpha, sc.alight->intensity));
	}
	else if (T[1] == 2)
	{
		t_sphere *sp = sc.objects->spheres[(int)T[2]];

		alpha = get_brightness_level(sp, sc.lights, create_point(sc.camera->o.x + T[0] * (screen_point->x - sc.camera->o.x),  sc.camera->o.y + T[0] * (screen_point->y - sc.camera->o.y), sc.camera->o.z + T[0] * (screen_point->z - sc.camera->o.z)));
		color = hexa(multiply_colors(sp->color, sc.lights->color, alpha, sc.alight->intensity)); 
	}
	else if (T[1] == 3)
	{
		t_cylinder *cy = sc.objects->cylinders[(int)T[2]];

		alpha = get_brightness_level_cylinder(cy, sc.lights, create_point(0 + T[0] * (screen_point->x - 0),  0 + T[0] * (screen_point->y - 0), 0 + T[0] * (screen_point->z - 0)));
		color = hexa(cy->color); 
	}
	my_mlx_pixel_put(data, x, y, color);
}

void render_screen(t_data *data, t_scene *scene)
{
	int i;
	int j;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			render_pixel(j, i, data, *scene);
			j++;
		}
		i++;
	}
}
