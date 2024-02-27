/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user4t <user4t@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:16:53 by carlosga          #+#    #+#             */
/*   Updated: 2024/02/27 20:27:24 by user4t           ###   ########.fr       */
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
	//t_vector	v1;
	t_vector	v2;
	t_vector	v3;
	double		alpha;

	/*---- NO CAMBIAR ESTE BLOQUE ----*/
	//v1 = *create_vector(*p, s->o);
	v2 = *create_vector(l->o, *p);
	v3 = *create_vector(l->o, s->o);
	alpha = module(v2) - module(v3) + s->radius;
	alpha = (1 - (alpha / s->radius)) * l->intensity;
	/*--------------------------------*/

	//v1 = unit_vector(*create_vector(s->o, *p));
	//v2 = unit_vector(*create_vector(*p, l->o));
	//v3 = unit_vector(*create_vector(*p, l->o));
	//alpha = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z / (module(v1) * module(v2));
	////alpha = v1.x * v2.y + v2.x * v1.y + v1.y * v2.z + v2.y * v1.z + v1.z * v2.x + v2.z * v1.x;
	//printf("v1: (%f, %f, %f), v2: (%f, %f, %f), alpha: %f\n", v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, alpha);
	//alpha = alpha * l->intensity;
	////alpha = (255 * s->radius * 2 * alpha) * l->intensity / module(v2);
	//printf("alpha = %f; module v2 = %f\n", alpha, module(v2));
	return (alpha);
}


