/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:52:44 by dximenez          #+#    #+#             */
/*   Updated: 2024/06/27 14:03:46 by dximenez         ###   ########.fr       */
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
