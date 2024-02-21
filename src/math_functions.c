/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:44:53 by carlosga          #+#    #+#             */
/*   Updated: 2024/02/21 16:21:49 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int x_pos(int x)
{
    return (x + WIN_WIDTH / 2 - WIN_WIDTH);
}

int y_pos(int y)
{
    return (-y - WIN_HEIGHT / 2 + WIN_HEIGHT);
}

double module(t_vector v)
{
	return(sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_cords *get_screen_coord(int x, int y, int fov)
{
	t_cords	*coords;
	double	limit;
	
	limit = tan(fov/2);	
	coords = malloc(sizeof(t_cords));
	coords->x = x * limit / 1080;
	coords->y = y * limit / 1080;
	coords->z = -1;
	return(coords);
}
