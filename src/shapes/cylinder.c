/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:18:32 by carlosga          #+#    #+#             */
/*   Updated: 2024/02/28 13:02:28 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_cylinder  *create_cylinder(int x, int y, int z, double vx, double vy, double vz, double radius, double height, int color)
{
	t_cylinder	*cy;

	cy = malloc(sizeof(t_plane));
	cy->o.x = x;
	cy->o.y = y;
	cy->o.z = z;
	cy->v.x = vx;
	cy->v.y = vy;
	cy->v.z = vz;
    cy->radius = radius;
    cy->height = height;
	cy->color = rgb(color);
	return (cy);
}

double  vector_x_cylinder(t_cylinder cy, t_vector v)
{
	double	t[2];
	double	a;
	double	b;
	double	c;
	double	D;
	
	v = unit_vector(v);
	a = pow(v.x, 2) + pow(v.z, 2);
	b = 2 * v.x * (/*origen vector*/ 1 - cy.o.x) + 2 * v.z * (/*origen vector*/ 1 - cy.o.z);
	c = pow(v.x, 2) + pow(cy.o.x, 2)/* - 2 * cy.o.x * origen vector */ + pow(v.z, 2) + pow(cy.o.z, 2) + pow(cy.radius, 2);
	if (cy.height / 2 <= cy.o.y)
		D = b * b - (4 * a * c);
	else
		D = -1;
	//printf("a:%f b:%f c:%f D: %f ", a, b, c, D);
	if (D >= 0)
	{
		t[0] = (- b + sqrt(D)) / (2 * a);
		t[1] = (- b - sqrt(D)) / (2 * a);
	//	printf("t1:%f t2:%f ", t[0], t[1]);
	//	printf("\n");
		
		if (t[0] > t[1])
			return (t[0]);
		return (t[1]);
	}
	//printf("\n");
	return (0);
}

double get_brightness_level_cylinder(t_cylinder *c, t_light *l, t_cords *p)
{
	t_vector	v1;
	t_vector	v2;
	t_vector	v3;
	double		alpha;

	/*---- NO CAMBIAR ESTE BLOQUE ----*/
	v1 = *create_vector(c->o, *p);
	v2 = *create_vector(l->o, *p);
	v3 = *create_vector(l->o, c->o);
	alpha = module(v2) - module(v3) + c->radius;
	alpha = (1 - (alpha / c->radius)) * l->intensity;
	/*--------------------------------*/

	return (alpha);
}

