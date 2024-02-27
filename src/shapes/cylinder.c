/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:18:32 by carlosga          #+#    #+#             */
/*   Updated: 2024/02/27 18:10:44 by carlosga         ###   ########.fr       */
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
	
	printf("v: (%f, %f, %f) -> ", v.x, v.y, v.z);
	v = unit_vector(v);
	a = pow(cy.v.x, 2) + pow(cy.v.y, 2)/* + pow(cy.v.z, 2)*/;
	b = -2 * (v.x * (cy.v.x + cy.o.x) + v.y * (cy.v.y + cy.o.y)/* + v.z * (cy.v.z + cy.o.z)*/);
	c = pow(v.x, 2) + pow(cy.o.x, 2) - 2 * cy.o.x * v.x + pow(v.y, 2) + pow(cy.o.y, 2) - 2 * cy.o.y * v.y + /*pow(v.z, 2) + pow(cy.o.z, 2) - 2 * cy.o.z * v.z*/ - pow(cy.radius, 2);
    D = b * b - (4 * a * c);
	printf("a:%f b:%f c:%f D: %f ", a, b, c, D);
	if (D >= 0)
	{
		t[0] = (- b + sqrt(D)) / (2 * a);
		t[1] = (- b - sqrt(D)) / (2 * a);
		printf("t1:%f t2:%f ", t[0], t[1]);
		printf("\n");
		
		if (t[0] < t[1])
			return (t[0]);
		return (t[1]);
	}
	printf("\n");
	return (0);
}