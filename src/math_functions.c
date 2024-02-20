/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:44:53 by carlosga          #+#    #+#             */
/*   Updated: 2024/02/20 13:35:05 by carlosga         ###   ########.fr       */
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

double vector_x_sphere(t_sphere s, t_vector v)
{
	double	t[2];
	double	a;
	double	b;
	double	c;
	int	D;

	a = pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2);
	b = 2 * (v.x * (s.o.x - v.x) + v.y * (s.o.y - v.y) + v.z * (s.o.z - v.z));
	c = pow(s.o.x - v.x, 2) + pow(s.o.y - v.y, 2) + pow(s.o.z - v.z, 2) - pow(s.radius, 2);
	D = b * b - (4 * a * c);
	if (D >= 0)
	{
		t[0] = (- b + sqrt(D)) / (2 * a);
		t[1] = (- b - sqrt(D)) / (2 * a);
		if (t[0] < t[1])
			return (t[0]);
		return (t[1]);
	}
	return (0);
}

t_cords *get_screen_coord(int x, int y, int fov)
{
	t_cords	*coords;
	double	limit;
	
	limit = tan(fov/2);	
	coords = malloc(sizeof(t_cords));
	coords->x = x * limit / WIN_WIDTH;
	coords->y = y * limit / WIN_HEIGHT;
	coords->z = -1;
	return(coords);
}
