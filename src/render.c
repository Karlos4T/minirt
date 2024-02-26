/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:33:53 by carlosga          #+#    #+#             */
/*   Updated: 2024/02/26 17:00:14 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void render_pixel(int x, int y, t_data *data, t_scene sc)
{
	t_cords		*screen_point;
	t_vector	*vector;
	int color = 0X220022;
	double	t;
	double T[3];
	int i;
	double	alpha;

	T[0] = 0;
	screen_point = get_screen_coord(x_pos(x), y_pos(y), sc.camera->fov);
	vector = create_vector(*screen_point, *sc.camera->o);
	i = 0;
	while (sc.objects->planes[i] != NULL)
	{
		t = vector_x_plane(*sc.objects->planes[i], *vector);
		if (t && (fabs(t) < fabs(T[0]) || !T[0]))
		{
			T[0] = fabs(t);
			T[1] = 1;
			T[2] = i;
		}
		i++;
	}
	i = 0;
	while (sc.objects->spheres[i] != NULL)
	{
		t = vector_x_sphere(*sc.objects->spheres[i], *vector);
		if (t && (fabs(t) < fabs(T[0]) || !T[0]))
		{
			T[0] = t;
			T[1] = 2;
			T[2] = i;
		}
		i++;
	}
	if (T[1] == 1)
	{
		t_plane *pl = sc.objects->planes[(int)T[2]];
		
		alpha = get_brightness_level_plane(pl, sc.lights, create_point(0 + T[0] * (screen_point->x - 0),  0 + T[0] * (screen_point->y - 0), 0 + T[0] * (screen_point->z - 0)));
		//int rgb[] = {alpha * pl->color[0], alpha * pl->color[1], alpha * pl->color[2]};
		color = hexa(multiply_colors(pl->color, sc.lights->color, alpha, sc.lights->intensity));
	}
	else if (T[1] == 2)
	{
		t_sphere *sp = sc.objects->spheres[(int)T[2]];

		alpha = get_brightness_level(sp, sc.lights, create_point(0 + T[0] * (screen_point->x - 0),  0 + T[0] * (screen_point->y - 0), 0 + T[0] * (screen_point->z - 0)));
		color = hexa(multiply_colors(sp->color, sc.lights->color, alpha, sc.lights->intensity)); 
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
