/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:33:53 by carlosga          #+#    #+#             */
/*   Updated: 2024/02/24 11:41:30 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void render_pixel(int x, int y, t_data *data, t_scene sc)
{
	t_cords		*screen_point;
	t_vector	*vector;
	int color = 0X220022;
	double	t[4];
	double T = 0;
	int I;
	int i;
	double	alpha;

	screen_point = get_screen_coord(x_pos(x), y_pos(y), sc.camera->fov);
	vector = create_vector(*screen_point, *sc.camera->o);
	i = 0;
	while (sc.objects->planes[i] != NULL)
	{
		t[i] = vector_x_plane(*sc.objects->planes[i], *vector);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		if (fabs(t[i]) > fabs(T))
		{
			T = t[i];
			I = i;
		}
		i++;
	}
	if (T)
	{
		t_plane *pl = sc.objects->planes[I];
		
		alpha = get_brightness_level_plane(pl, sc.lights, create_point(0 + T * (screen_point->x - 0),  0 + T * (screen_point->y - 0), 0 + T * (screen_point->z - 0)));
		int rgb[] = {(int)alpha + pl->color[0] / 2, (int)alpha + pl->color[1] / 2, (int)alpha + pl->color[2] / 2};
		color = hexa(rgb);
	}
	i = 0;
	while (sc.objects->spheres[i] != NULL)
	{
		t[0] = vector_x_sphere(*sc.objects->spheres[i], *vector);
		if (t[0])
		{
			alpha = get_brightness_level(sc.objects->spheres[i], sc.lights, create_point(0 + t[0] * (screen_point->x - 0),  0 + t[0] * (screen_point->y - 0), 0 + t[0] * (screen_point->z - 0)));
			color = hexa(multiply_colors(sc.objects->spheres[i]->color, sc.lights->color, alpha, sc.lights->intensity)); 
		}
		i++;
	}

	my_mlx_pixel_put(data, x, y, color);
}

void render_screen(t_data *data, t_scene *scene)
{
	int i;
	int j;

	i = 0;
	while (i < WIN_WIDTH)
	{
		j = 0;
		while (j < WIN_HEIGHT)
		{
			render_pixel(i, j, data, *scene);
			j++;
		}
		i++;
	}
}
