/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:44:46 by carlosga          #+#    #+#             */
/*   Updated: 2024/03/13 13:54:00 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_plane *create_plane(int x, int y, int z, double vx, double vy, double vz, int color)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	plane->o.x = x;
	plane->o.y = y;
	plane->o.z = z;
	plane->v.x = vx;
	plane->v.y = vy;
	plane->v.z = vz;
	plane->color = rgb(color);
	return (plane);
}

double vector_x_plane(t_plane pl, t_vector v)
{
	double t;

	t = (pl.v.x * pl.o.x + pl.v.y * pl.o.y + pl.v.z * pl.o.z) / (pl.v.x * v.x + pl.v.y * v.y + pl.v.z * v.z);
	return (t);
}

double get_brightness_level_plane(t_plane *pl, t_light *l, t_cords *p)
{
	t_vector	v1;
	//t_vector	v2;
	double		alpha;

	(void) p;

//	v1 = malloc(sizeof(t_vector));
//	v1->x = pl->v.x + p->x;
//	v1->y = pl->v.y + p->y;
//	v1->z = pl->v.z + p->z;
//	//printf("p: (%f, %f, %f)\n", p->x, p->y, p->z);
//	v2 = *create_vector(l->o, *p);
//	//alpha = (v1->x * v2.x + v1->y * v2.y + v1->z * v2.z)/* / (module(*v1) * module(v2))*/;
//	//printf("alpha = %f\n", alpha);
//	//alpha = (pow(alpha, 2) * (1 - module(v2) / 10000)) * l->intensity;
//	alpha = pow(/*module(normalize(v2)) */ 6 / sqrt(module(v2)), 2) * l->intensity;
//	//if (module(v2) > 700)
//	//printf("vector: (%f, %f, %f) modulev2 = %f\n", v2.x, v2.y, v2.z, module(v2));
	
	/*NEW FORM*/
	v1 = normalize(*create_vector(l->o, pl->o));
	alpha = dot(v1, neg(pl->v)) * 0.5 + 0.5;

	printf("%f\n", alpha);
	if (alpha < 0)
		return (0);
	
	/*--------*/
	
	return (alpha);
}

int check_shadow(t_cords p, t_cords l, t_sphere **s)
{
	t_vector 	*v;
	int			i;

	i = 0;
	v = create_vector(p, l);
	while (s[i])
	{
		if (vector_x_sphere(*s[i], *v, p))
		{	
			//printf("p(%f, %f, %f)\n", p.x, p.y, p.z);
			//printf("l(%f, %f, %f)\n", l.x, l.y, l.z);
			//printf("s(%f, %f, %f)\n", s[i]->o.x , s[i]->o.x, s[i]->o.x);
			return (1);
		}
		i++;
	}
	return (0);
}