/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:32:20 by carlosga          #+#    #+#             */
/*   Updated: 2024/06/27 13:56:35 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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
	int	result[3];
	int	ambient[3];
	int	diffuse[3];
	int	combined[3];
	int	res;

	scale_color(ambient, sc.amb->color, sc.amb->intensity);
	if (is_shadow)
		scale_color(diffuse, sc.light->color, 0);
	else
		scale_color(diffuse, sc.light->color,
			sc.light->intensity * fmaxf(alpha, 0));
	add_colors(combined, ambient, diffuse);
	multiply_colors(result, surface_color, combined);
	res = result[0] << 16 | result[1] << 8 | result[2];
	return (res);
}
