/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_functions3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:05:17 by dximenez          #+#    #+#             */
/*   Updated: 2024/06/27 14:13:27 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

double	dot_prod(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double	quadratic(double a, double b, double c)
{
	double	d;
	double	t[2];

	d = b * b - (4 * a * c);
	if (d >= 0)
	{
		t[0] = (-b + sqrt(d)) / (2 * a);
		t[1] = (-b - sqrt(d)) / (2 * a);
		if (fabs(t[0]) < fabs(t[1]))
			return (t[0]);
		return (t[1]);
	}
	return (0);
}

t_vec	*get_screen_coord(int x, int y, t_camera *c)
{
	t_vec		*coords;
	double		wsize;
	const t_vec	global_up = {0.0f, 1.0f, 0.0f};
	const t_vec	right = normalize(cross_prod(global_up, c->v));
	const t_vec	up = normalize(cross_prod(c->v, right));

	coords = malloc(sizeof(t_vec));
	if (!coords)
		return (NULL);
	wsize = fabs(tan((c->fov * (M_PI / 180.0)) / 2));
	coords->x = c->o.x - (x * wsize / WIN_HEIGHT) * right.x
		- (y * wsize / WIN_HEIGHT) * up.x - c->v.x;
	coords->y = c->o.y + (x * wsize / WIN_HEIGHT) * right.y
		+ (y * wsize / WIN_HEIGHT) * up.y + c->v.y;
	coords->z = c->o.z + (x * wsize / WIN_HEIGHT) * right.z
		+ (y * wsize / WIN_HEIGHT) * up.z + c->v.z;
	return (coords);
}

double	map_value(double x)
{
	const double	x_min = 1.0;
	const double	x_max = 1.75;
	const double	y_min = 0.25;
	const double	y_max = 0.72;

	return (y_min + ((x - x_min) / (x_max - x_min)) * (y_max - y_min));
}
