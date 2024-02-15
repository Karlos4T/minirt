/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:07:20 by carlosga          #+#    #+#             */
/*   Updated: 2024/02/15 13:31:42 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

t_sphere *create_sphere(int x, int y, int z, int radius, int color)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	sphere->o->x = x;
	sphere->o->y = y;
	sphere->o->z = z;
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

void render_screen(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			render_pixel(i, j, data);
			j++;
		}
		i++;
	}
}