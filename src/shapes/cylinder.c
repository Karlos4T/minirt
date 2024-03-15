/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:18:32 by carlosga          #+#    #+#             */
/*   Updated: 2024/03/15 17:12:33 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_cylinder	*create_cylinder(int x, int y, int z, double vx, double vy, double vz, double radius, double height, int color)
{
	t_cylinder	*cy;
	
	cy = malloc(sizeof(t_cylinder));

	cy->o.x = x;
	cy->o.y = y;
	cy->o.z = z;
	cy->v.x = vx;
	cy->v.y = vy;
	cy->v.z = vz;
    cy->radius = radius;
    cy->height = height;
	cy->covers[0] = create_plane(cy->o.x + cy->height / 2 * cy->v.x, cy->o.y + cy->height / 2 * cy->v.y, cy->o.z + cy->height / 2 * cy->v.z, cy->v.x, cy->v.y, cy->v.z, 0X00FFFFFF);
	cy->covers[1] = create_plane(cy->o.x - cy->height / 2 * cy->v.x, cy->o.y - cy->height / 2 * cy->v.y, cy->o.z - cy->height / 2 * cy->v.z, cy->v.x, cy->v.y, cy->v.z, 0X00FFFFFF);
	cy->color = rgb(color);
	return (cy);
}


int cut_cylinder(t_cylinder cy, t_vec v, double t)
{
	t_vec *p;
	double t1, t2;
	
	t1 = ((cy.o.x - 0) * cy.v.y - (cy.o.y - 0) * cy.v.x) / (v.x * cy.v.y - v.y * cy.v.x);
    t2 = ((0 - cy.o.x) * v.y - (0 - cy.o.y) * v.x) / (cy.v.x * v.y - cy.v.y * v.x);
	/*RESTAR EL RADIO AL PUNTO DE CORTE, CHEQUEAR QUE SEA UN 
	PUNTO EN EL EJE Y HACER EL VECTOR DESDE ESE PUNTO AL CENTRO*/
	p = malloc(sizeof(t_vec));
	p->x = cy.o.x + t2 * cy.v.x;
	p->y = cy.o.y + t2 * cy.v.y;
	p->z = cy.o.z + t2 * cy.v.z;
	if (p->y == 50)
	{
		printf("v(%f, %f, %f)\n", p->x, p->y, p->z);
	}	
	//printf("%f, %f)\n", module(*p), cy.height);

	if (module(*p) > cy.height/2)
		return (0);
	return t;
}

double	vector_x_cylinder(t_cylinder cy, t_vec r, t_vec o)
{

	t_vec		*u;
	t_vec		*v;
	double		a;
	double		b;
	double		c;

	u = cross_prod(r, cy.v);
	v = vec_sub(cy.o, o);
	v = cross_prod(*v, cy.v);
	a = dot_prod(*u, *u);
	b = 2 * dot_prod(*u, *v);
	c = dot_prod(*v, *v) - cy.radius * cy.radius;
	return (cut_cylinder(cy, r, quadratic(a, b, c)));
}


double plane_x_cylinder(t_cylinder cy, t_vec v)
{
	int		t;
	t_plane	*pl;

	pl = create_plane(cy.o.x + cy.height / 2 * cy.v.x,  cy.o.y + cy.height / 2 * cy.v.y, cy.o.z + cy.height / 2 * cy.v.z, cy.v.x, cy.v.y, cy.v.z, hexa(cy.color));
	t = - (pl->o.x * cy.o.x + pl->o.y * cy.o.y + pl->o.z * cy.o.z + cy.height/2) / (pl->o.x * v.x + pl->o.y * v.y + pl->o.z * v.z);
	return (t);
}

