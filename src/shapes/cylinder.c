/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:18:32 by carlosga          #+#    #+#             */
/*   Updated: 2024/04/08 16:59:06 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_cylinder	*create_cylinder(int x, int y, int z, double vx, double vy, double vz, double diameter, double height, int color)
{
	t_cylinder	*cy;
	
	cy = malloc(sizeof(t_cylinder));

	cy->o.x = x;
	cy->o.y = y;
	cy->o.z = z;
	cy->v.x = vx;
	cy->v.y = vy;
	cy->v.z = vz;
    cy->radius = diameter / 2;
	cy->is_cover = 0;
	cy->r2 = diameter * diameter * 0.25;
	if (module(cy->v) > 1)
    	cy->r2 = diameter * diameter * 0.50;
    cy->height = height;
	cy->covers[0] = create_plane(cy->o.x + dot_prod(cy->v, *vec(1, 0, 0)) / (module(cy->v) * module(*vec(1, 0, 0))) * (cy->height / 2), \
		cy->o.y + dot_prod(cy->v, *vec(0, 1, 0)) / (module(cy->v) * module(*vec(0, 1, 0))) * (cy->height / 2), \
		cy->o.z + dot_prod(cy->v, *vec(0, 0, 1)) / (module(cy->v) * module(*vec(0, 0, 1))) * (cy->height / 2), \
		cy->v.x, cy->v.y, cy->v.z, color);
	cy->covers[1] = create_plane(cy->o.x - dot_prod(cy->v, *vec(1, 0, 0)) / (module(cy->v) * module(*vec(1, 0, 0))) * (cy->height / 2), \
		cy->o.y - dot_prod(cy->v, *vec(0, 1, 0)) / (module(cy->v) * module(*vec(0, 1, 0))) * (cy->height / 2), \
		cy->o.z - dot_prod(cy->v, *vec(0, 0, 1)) / (module(cy->v) * module(*vec(0, 0, 1))) * (cy->height / 2), \
		-cy->v.x, -cy->v.y, -cy->v.z, color);
	cy->color = rgb(color);
	return (cy);
}

int cut_cylinder(t_cylinder cy, t_ray r, double t)
{
	t_vec pc;
	t_vec po;
	double hip;

	pc = get_point(r, t);
	po = vec_sub(pc, cy.o);
	hip = module(po);
	if(hip-1 > sqrt(pow(cy.height/2, 2) + pow(cy.radius, 2)))
		return (0);
	return (t);
}
/*
double cylinder_covers(t_cylinder *cy, t_vec v)
{
	t_vec		*cp;
	int			i;

	i = 0;
	while (i < 2)
	{
		double tp = vector_x_plane(*cy->covers[i], v);
		if(tp)
		{
			cp = vec(0 - v.x * tp, 0 - v.y * tp, 0 - v.z * tp);
			if (module(vec_sub(*cp, cy->covers[i]->o)) <= cy->radius)
			{
				cy->is_cover = i + 1;
				printf("%f\n", tp);
				return (tp);
			}
		}
		i++;
	}
	return (0);
}
*/

double cylinder_covers(t_cylinder *cy, t_ray r)
{
	t_vec		cp;
	int			i;
	double		tp[2];
	
	i = 0;
	while (i < 2)
	{
		tp[i] = vector_x_plane(*cy->covers[i], r);
		i++;
	}
	i = 0;
	if(fabs(tp[1]) < fabs(tp[0]))
		i = 1;
	cp = get_point(r, fabs(tp[i]));
	//if (module(r.o) != 0 && tp[i])
	//	printf("%d\n", i);
		//printf("r(%f, %f, %f)\n", r.v.x, r.v.y, r.v.z);
	//	printf("r.o(%f, %f, %f) -> %f\n", v.x, v.y, v.z, tp[i]);
	if (module(vec_sub(cp, cy->covers[i]->o)) <= cy->radius)
	{
		cy->is_cover = i + 1;
		return (tp[i]);
	}
	return 0;
}

double	vector_x_cylinder(t_cylinder *cy, t_ray r)
{
	t_vec		u;
	t_vec		v;
	double		a;
	double		b;
	double		c;
	double		t[2];

	u = cross_prod(r.v, cy->v);
	v = vec_sub(r.o, cy->o);
	v = cross_prod(v, cy->v);
	a = dot_prod(u, u);
	b = 2 * dot_prod(u, v);
	c = dot_prod(v, v) - cy->r2;
	t[0] = cylinder_covers(cy, r);
	t[1] = cut_cylinder(*cy, r, quadratic(a, b, c));
	if (t[1])
	{
		cy->is_cover = 0;
		return t[1];
	}
	else if (t[0])
		return t[0];
	return 0;
}

double plane_x_cylinder(t_cylinder cy, t_vec v)
{
	int			t;
	t_plane		*pl;

	pl = create_plane(cy.o.x + cy.height / 2 * cy.v.x,  cy.o.y + cy.height / 2 * cy.v.y, cy.o.z + cy.height / 2 * cy.v.z, cy.v.x, cy.v.y, cy.v.z, hexa(cy.color));
	t = - (pl->o.x * cy.o.x + pl->o.y * cy.o.y + pl->o.z * cy.o.z + cy.height/2) / (pl->o.x * v.x + pl->o.y * v.y + pl->o.z * v.z);
	return (t);
}
