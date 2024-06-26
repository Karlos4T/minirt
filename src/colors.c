/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:32:20 by carlosga          #+#    #+#             */
/*   Updated: 2024/06/26 16:57:01 by dximenez         ###   ########.fr       */
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
	return (hexa);
}

void	scale_color(int *result, int *color, float scale)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		result[i] = fminf(color[i] * scale, 255);
		i++;
	}
}

void	add_colors(int *result, int *a, int *b)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		result[i] = fminf(a[i] + b[i], 255);
		i++;
	}
}

void	multiply_colors(int *result, int *a, int *b)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		result[i] = fminf(a[i] * b[i] / 255.0f, 255);
		i++;
	}
}

int	calculate_color(t_scene sc, int *surface_color, float alpha, int is_shadow)
{
	int	*result;
	int	ambient[3];
	int	diffuse[3];
	int	combined[3];
	int	res;

	result = malloc(sizeof(int) * 3);
	scale_color(ambient, sc.amb->color, sc.amb->intensity);
	if (is_shadow)
		scale_color(diffuse, sc.light->color, 0);
	else
		scale_color(diffuse, sc.light->color,
			sc.light->intensity * fmaxf(alpha, 0));
	add_colors(combined, ambient, diffuse);
	multiply_colors(result, surface_color, combined);
	res = result[0] << 16 | result[1] << 8 | result[2];
	// free(result);
	return (res);
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