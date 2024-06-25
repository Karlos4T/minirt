/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:32:20 by carlosga          #+#    #+#             */
/*   Updated: 2024/06/25 17:42:26 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	*rgb(int color)
{
	int	*rgb;

	rgb = malloc(sizeof(int) * 3);
	rgb[0] = (color) >> 16 & 0xFF;
	rgb[1] = (color) >> 8 & 0xFF;
	rgb[2] = (color) & 0xFF;
	return (rgb);
}

int	hexa(int *rgb)
{
	int	hexa;
	int	i;

	i = 0;
	if (!rgb)
		return (0);
	while (i < 3)
	{
		if (rgb[i] < 0)
			rgb[i] = 0;
		else if (rgb[i] > 255)
			rgb[i] = 255;
		i++;
	}
	hexa = (rgb[0] << 16) + (rgb[1] << 8) + rgb[2];
	//free(rgb);
	return (hexa);
}

void scale_color(int *result, int *color, float scale) {
    for (int i = 0; i < 3; i++) {
        result[i] = fminf(color[i] * scale, 255);
    }
}

void add_colors(int *result, int *a, int *b) {
    for (int i = 0; i < 3; i++) {
        result[i] = fminf(a[i] + b[i], 255);
    }
}

void multiply_colors(int *result, int *a, int *b) {
    for (int i = 0; i < 3; i++) {
        result[i] = fminf(a[i] * b[i] / 255.0f, 255);
    }
}

int *calculate_color(int *surface_color, int *ambient_color, float ambient_intensity, int *point_color, float point_intensity, float alpha, int is_shadow)
{
	int	*result;
	int	ambient[3];
	int	diffuse[3];
	int	combined[3];

	result = malloc(sizeof(int) * 3);
	scale_color(ambient, ambient_color, ambient_intensity);
	if (is_shadow)
		scale_color(diffuse, point_color, 0);
	else
		scale_color(diffuse, point_color, point_intensity * fmaxf(alpha, 0));
	add_colors(combined, ambient, diffuse);
	multiply_colors(result, surface_color, combined);
	return (result);
}

/*
//FUNCIÓN DE GESTION DE ILUMINACIÓN ORIGINAL
    int	*rgb;
	int	i;

    (void)point_color;
    (void)point_intensity;

	i = 0;
	rgb = malloc(sizeof(int) * 3);
	while (i < 3)
	{	
		if (is_shadow)
		{
			// printf("%d\n", is_shadow);
			rgb[i] = surface_color[i] * ambient_intensity;
		}
		else
			rgb[i] = sqrt(surface_color[i] * ambient_color[i]) * alpha;
		if (rgb[i] < + ambient_intensity * surface_color[i])
			rgb[i] = ambient_intensity * surface_color[i];
		i++;
	}
	return (rgb);
*/