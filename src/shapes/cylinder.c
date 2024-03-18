/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:18:32 by carlosga          #+#    #+#             */
/*   Updated: 2024/03/18 14:02:33 by carlosga         ###   ########.fr       */
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
	cy->covers[0] = create_plane(cy->o.x + (cy->height / 2) * cy->v.x, cy->o.y + (cy->height / 2) * cy->v.y, cy->o.z + (cy->height / 2) * cy->v.z, cy->v.x, cy->v.y, cy->v.z, color);
	cy->covers[1] = create_plane(cy->o.x - cy->height / 2 * cy->v.x, cy->o.y - cy->height / 2 * cy->v.y, cy->o.z - cy->height / 2 * cy->v.z, cy->v.x, cy->v.y, cy->v.z, color);
	cy->color = rgb(color);
	return (cy);
}


int cut_cylinder(t_cylinder cy, t_vec v, double t)
{
	t_vec *pc;
	t_vec *po;
	double hip;

	pc = vec(0 + t*v.x, 0 + t*v.y, 0 + t*v.z);
	po = vec(pc->x + cy.o.x, pc->y + cy.o.y, pc->z + cy.o.z);
	hip = module(*po);
	//printf("pc(%f, %f, %f)\n", pc->x, pc->y, pc->z);
	//printf("po(%f, %f, %f)\n", po->x, po->y, po->z);

	//printf("%f, %f\n", hip, sqrt(pow(cy.height/2, 2) + pow(cy.radius, 2)));
	//if(hip < sqrt(pow(cy.height/2, 2) + pow(cy.radius, 2)))
	//	return (0);
	
	if(hip > sqrt(pow(cy.height/2, 2) + pow(cy.radius, 2)))
		return (0);
	//if (hip == sqrt(pow(cy.height/2, 2) + pow(cy.radius, 2)))
	//{
	//}
	return (0);
}

double	vector_x_cylinder(t_cylinder cy, t_vec r, t_vec o)
{

	t_vec		*u;
	t_vec		*v;

	t_vec		*cp;

	double		a;
	double		b;
	double		c;

	u = cross_prod(r, cy.v);
	v = vec_sub(cy.o, o);
	v = cross_prod(*v, cy.v);
	a = dot_prod(*u, *u);
	b = 2 * dot_prod(*u, *v);
	c = dot_prod(*v, *v) - cy.radius * cy.radius;
	int tp = vector_x_plane(*cy.covers[0], r);
	if(tp)
	{
		cp = vec(r.x * tp, r.y * tp, r.z * tp);
		//printf("v(%f, %f, %f)\n", r.x, r.y, r.z);
		//printf("cp(%f, %f, %f)\n", cp->x, cp->y, cp->z);
		//printf("o(%f, %f, %f)\n", cy.covers[0]->o.x, cy.covers[0]->o.y, cy.covers[0]->o.z);
		//printf("v(%f, %f, %f)\n", cy.covers[0]->v.x, cy.covers[0]->v.y, cy.covers[0]->v.z);
		//printf("%f\n", module(*create_vector(*cp, cy.covers[0]->o)));
		if (module(*create_vector(*cp, cy.covers[0]->o)) <= cy.radius)
		{
			printf("Corta el plano");
			return (tp);
		}
		return(0);
	}
	if (quadratic(a, b, c))
		return (cut_cylinder(cy, r, quadratic(a, b, c)));
	return 0;
}


double plane_x_cylinder(t_cylinder cy, t_vec v)
{
	int		t;
	t_plane	*pl;

	pl = create_plane(cy.o.x + cy.height / 2 * cy.v.x,  cy.o.y + cy.height / 2 * cy.v.y, cy.o.z + cy.height / 2 * cy.v.z, cy.v.x, cy.v.y, cy.v.z, hexa(cy.color));
	t = - (pl->o.x * cy.o.x + pl->o.y * cy.o.y + pl->o.z * cy.o.z + cy.height/2) / (pl->o.x * v.x + pl->o.y * v.y + pl->o.z * v.z);
	return (t);
}

