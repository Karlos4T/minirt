/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:32:20 by carlosga          #+#    #+#             */
/*   Updated: 2024/02/21 13:38:19 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int *rgb(int color)
{
	int *rgb;

	rgb = malloc(sizeof(int) * 3);
	rgb[0] = (color) >> 16 & 0xFF;
	rgb[1] = (color) >> 8 & 0xFF;
	rgb[2] = (color) & 0xFF;

	return (rgb);
}

int hexa(int *rgb)
{
	int hexa;
    int i;
    
    i = 0;
    while (i < 3)
    {
        if (rgb[i] < 0)
            rgb[i] = 0;
        else if (rgb[i] > 255)
            rgb[i] = 255;
        i++;
    }
	hexa = (rgb[0] << 16) + (rgb[1] << 8) + rgb[2];
	return (hexa);
}



double get_brightness_level_plane(t_plane *pl, t_light *l, t_cords *p)
{
	t_vector	*v1;
	t_vector	v2;
	double		alpha;

	v1 = malloc(sizeof(t_vector));
	v1->x = pl->v.x + pl->o.x;
	v1->y = pl->v.y + pl->o.y;
	v1->z = pl->v.z + pl->o.z;
	v2 = *create_vector(*p, l->o);
	alpha = v1->x * v2.x + v1->y * v2.y + v1->z * v2.z;
	alpha = (255 - alpha / 255) * l->intensity;
	//printf("alpha = %f\n", alpha);
	return (alpha);
}

int *multiply_colors(int *rgb1, int *rgb2, double alpha, double intensity)
{
	int *rgb;
	int i;

	i = 0;
	rgb = malloc(sizeof(int) * 3);
	while (i < 3)
	{	
		if (rgb2[i] > 0)
			rgb[i] = (rgb1[i] + rgb2[i] * intensity) * alpha / 255;
		else
			rgb[i] = (rgb1[i] * intensity) * alpha / 255;
		i++;
	}
	return (rgb);
}
