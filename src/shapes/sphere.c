/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:16:53 by carlosga          #+#    #+#             */
/*   Updated: 2024/02/21 16:42:52 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_sphere	*create_sphere(int x, int y, int z, int radius, int color)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	sphere->o.x = x;
	sphere->o.y = y;
	sphere->o.z = z;
	sphere->radius = radius;
	sphere->color = rgb(color);

	return sphere;
}

double	vector_x_sphere(t_sphere s, t_vector v)
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

double get_brightness_level(t_sphere *s, t_light *l, t_cords *p)
{
	t_vector	*v1;
	t_vector	*v2;
	double		alpha;

	v1 = create_vector(s->o, *p);
	v2 = create_vector(s->o, l->o);
	alpha = v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
	alpha = (255 - s->radius * 2 * alpha / 255);
	return (alpha);
}