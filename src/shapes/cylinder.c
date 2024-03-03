/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:18:32 by carlosga          #+#    #+#             */
/*   Updated: 2024/03/03 13:05:38 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_cylinder	*create_cylinder(int x, int y, int z, double vx, double vy, double vz, double radius, double height, int color)
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

double	vector_x_cylinder(t_cylinder cy, t_vector v)
{
	double	t[2];
	double	a;
	double	b;
	double	c;
	double	D;
	double v1[2];
	double co[2];
	//dependiendo de la direccion que introduzca se cogera un valor u otro para operar
	if(cy.v.y == 1)
	{
		v1[0] = v.x;
		v1[1] = v.z;
		co[0] = cy.o.x;
		co[1] = cy.o.z;
	}
	else if(cy.v.x == 1)
	{
		v1[0] = v.y;
		v1[1] = v.z;
		co[0] = cy.o.y;
		co[1] = cy.o.z;
	}
	else if(cy.v.z == 1)
	{
		v1[0] = v.y;
		v1[1] = v.x;
		co[0] = cy.o.y;
		co[1] = cy.o.x;
	}
	//v = unit_vector(v); //esta linea curva el cilindro en funcion de x. Curioso
	a = pow(v1[0], 2) + pow(v1[1], 2);
	b = 2 * v1[0] * (/*origen vector*/ 1 - co[0]) + 2 * v1[1] * (/*origen vector*/ 1 - co[1]);
	c = pow(v1[0], 2) + pow(co[0], 2)/* - 2 * cy.o.x * origen vector */ + pow(v1[1], 2) + pow(co[1], 2) - pow(cy.radius, 2);
	if (cy.height / 2 + cy.o.y)
		D = b * b - (4 * a * c);
	else
		D = -1;
	//printf("v (x:%f y:%f z:%f)", v.x, v.y, v.z);
	//printf("cy(x:%f y:%f z:%f) ", cy.o.x, cy.o.y, cy.o.z);
	//printf("a:%f b:%f c:%f D: %f ", a, b, c, D);
	if (D >= 0)
	{
		t[0] = (- b + sqrt(D)) / (2 * a);
		t[1] = (- b - sqrt(D)) / (2 * a);
	//	printf("t1:%f t2:%f ", t[0], t[1]);
	//	printf("\n");
		printf("\n");
		if (t[0] > t[1])
			return (t[0]);
		return (t[1]);
	}
	return (0);
}

double	get_brightness_level_cylinder(t_cylinder *c, t_light *l, t_cords *p)
{
	//t_vector	*v1;
	t_vector	*v2;
	t_vector	*v3;
	double		alpha;

	//v1 = create_vector(c->o, *p);
	v2 = create_vector(l->o, *p);
	v3 = create_vector(l->o, c->o);
	alpha = module(*v2) - module(*v3) + c->radius;
	alpha = (1 - (alpha / c->radius)) * l->intensity;
	//free(v1);
	free(v2);
	free(v3);
	return (alpha);
}
