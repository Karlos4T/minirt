/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:16:53 by carlosga          #+#    #+#             */
/*   Updated: 2024/03/14 11:45:53 by carlosga         ###   ########.fr       */
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

double	vector_x_sphere(t_sphere s, t_vec v, t_vec vo)
{
	double	t[2];
	double	a;
	double	b;
	double	c;
	double	D;
	
	//v = normalize(v);
	a = dot(v, v);
	b = 2 * (v.x * (vo.x - s.o.x) + v.y * (vo.y - s.o.y) + v.z * (vo.z - s.o.z));
	c = pow(vo.x - s.o.x, 2) + pow(vo.y - s.o.y, 2) + pow(vo.z - s.o.z, 2) - pow(s.radius, 2);
	
	D = b * b - (4 * a * c);
	if (D >= 0)
	{
		//printf("v(%f, %f, %f) D = %f\n", v.x, v.y, v.z, D);
		t[0] = (- b + sqrt(D)) / (2 * a);
		t[1] = (- b - sqrt(D)) / (2 * a);
		if (fabs(t[0]) < fabs(t[1]))
			return (t[0]);
		return (t[1]);
	}
	return (0);
}

double get_brightness_level(t_sphere *s, t_light *l, t_vec *p)
{
	t_vec	v1;
	t_vec	v2;
	double		alpha;

	/*---- NO CAMBIAR ESTE BLOQUE ----*/
	//v1 = *create_vector(*p, s->o);
	/*v1 = create_vector(l->o, *p);
	v2 = create_vector(l->o, s->o);
	alpha = module(*v1) - module(*v3) + s->radius;
	alpha = (1 - (alpha / s->radius)) * l->intensity;*/
	/*--------------------------------*/

	v1 = normalize(*create_vector(s->o, *p));
	v2 = normalize(*create_vector(l->o, s->o));
	alpha = dot(v1, neg(v2)) / (module(v1) * module(v2));
	if (alpha < 0)
		return (0);
	//if (alpha < 0)
	//printf("v1(%f, %f, %f) v2(%f, %f, %f) alpha_norm = %f\n", v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, alpha);
	//alpha = module(v2) - module(v3) + s->radius;
	//alpha = (1 - (alpha / s->radius)) * l->intensity;
	
	//free(v2);
	//free(v3);
	//v1 = unit_vec(*create_vector(s->o, *p));
	//v2 = unit_vec(*create_vector(*p, l->o));
	//v3 = unit_vec(*create_vector(*p, l->o));
	//alpha = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z / (module(v1) * module(v2));
	////alpha = v1.x * v2.y + v2.x * v1.y + v1.y * v2.z + v2.y * v1.z + v1.z * v2.x + v2.z * v1.x;
	//printf("v1: (%f, %f, %f), v2: (%f, %f, %f), alpha: %f\n", v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, alpha);
	//alpha = alpha * l->intensity;
	////alpha = (255 * s->radius * 2 * alpha) * l->intensity / module(v2);
	//printf("alpha = %f; module v2 = %f\n", alpha, module(v2));
	return (alpha);
}


