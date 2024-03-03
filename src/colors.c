/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:32:20 by carlosga          #+#    #+#             */
/*   Updated: 2024/03/03 11:55:27 by carlosga         ###   ########.fr       */
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
	//free(rgb);
	return (hexa);
}

int *multiply_colors(int *rgb1, int *rgb2, double alpha, double al)
{
	int	*rgb;
	int	i;

	(void) rgb2;
	i = 0;
	rgb = malloc(sizeof(int) * 3);
	while (i < 3)
	{	
		rgb[i] = sqrt(rgb1[i] * rgb2[i]) * alpha;
		if (rgb[i] < + al * rgb1[i])
			rgb[i] = al * rgb1[i];
		//if (rgb2[i] > 0)
		//	rgb[i] = (rgb1[i] + rgb2[i] * intensity) * alpha / 255;
		//else
		//	rgb[i] = (rgb1[i] * intensity) * alpha / 255;
		i++;
	}
	return (rgb);
}