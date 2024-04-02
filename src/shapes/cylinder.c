/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:18:32 by carlosga          #+#    #+#             */
/*   Updated: 2024/04/02 17:50:58 by carlosga         ###   ########.fr       */
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
	cy->r2 = diameter * diameter * 0.25;
	//if (module(cy->v) > 1)
    //	cy->r2 = diameter * diameter * 0.30;
    cy->height = height;
	cy->covers[0] = create_plane(cy->o.x + dot_prod(cy->v, *vec(1, 0, 0)) / (module(cy->v) * module(*vec(1, 0, 0))) * (cy->height / 2), \
		cy->o.y + dot_prod(cy->v, *vec(0, 1, 0)) / (module(cy->v) * module(*vec(0, 1, 0))) * (cy->height / 2), \
		cy->o.z + dot_prod(cy->v, *vec(0, 0, 1)) / (module(cy->v) * module(*vec(0, 0, 1))) * (cy->height / 2), \
		cy->v.x, cy->v.y, cy->v.z, color);
	cy->covers[1] = create_plane(cy->o.x - dot_prod(cy->v, *vec(1, 0, 0)) / (module(cy->v) * module(*vec(1, 0, 0))) * (cy->height / 2), \
		cy->o.y - dot_prod(cy->v, *vec(0, 1, 0)) / (module(cy->v) * module(*vec(0, 1, 0))) * (cy->height / 2), \
		cy->o.z - dot_prod(cy->v, *vec(0, 0, 1)) / (module(cy->v) * module(*vec(0, 0, 1))) * (cy->height / 2), \
		cy->v.x, cy->v.y, cy->v.z, color);
	cy->covers[0] = create_plane(cy->o.x + (cy->height / 2) * cy->v.x, cy->o.y + (cy->height / 2) * cy->v.y, cy->o.z + (cy->height / 2) * cy->v.z, cy->v.x, cy->v.y, cy->v.z, color);
	cy->covers[1] = create_plane(cy->o.x - cy->height / 2 * cy->v.x, cy->o.y - cy->height / 2 * cy->v.y, cy->o.z - cy->height / 2 * cy->v.z, cy->v.x, cy->v.y, cy->v.z, color);
	cy->color = rgb(color);
	return (cy);
}


int cut_cylinder(t_cylinder cy, t_vec v, double t)
{
	t_vec *pc;
	t_vec po;
	double hip;

	pc = vec(0 + t*v.x, 0 + t*v.y, 0 + t*v.z);
	po = vec_sub(*pc, cy.o);// (pc->x + cy.o.x, pc->y + cy.o.y, pc->z + cy.o.z);
	hip = module(po);
	//printf("%f, %f\n", hip, sqrt(pow(cy.height/2, 2) + pow(cy.radius, 2)));
	if(hip > sqrt(pow(cy.height/2, 2) + pow(cy.radius, 2)))
	{
		//printf("retorna 0\n");	
		return (0);
	}
	return (t);
}

double cylinder_covers(t_cylinder cy, t_vec v)
{
	t_vec		*cp;
	int			i;
	
	i = 0;
	while (i < 2)
	{
		double tp = vector_x_plane(*cy.covers[i], v);
		if(tp)
		{
			cp = vec(0 - v.x * tp, 0 - v.y * tp, 0 - v.z * tp);
			//printf("v(%f, %f, %f)\n", v.x, v.y, tp);
			//printf("cp(%f, %f, %f)\n", cp->x, cp->y, cp->z);
			//printf("r = %f, r2 = %f\n", cy.radius, cy.r2);
			if (module(*create_vector(*cp, cy.covers[i]->o)) <= cy.radius )
				return (tp);
		}
		i++;
	}
	return (0);
}
t_vec	multi_vect(const t_vec vect, const double x)
{
	return (*vec(vect.x * x, vect.y * x, vect.z * x));
}
t_vec	sub_vect(const t_vec vect1, const t_vec vect2)
{
	return (*vec(vect1.x - vect2.x, vect1.y - vect2.y, vect1.z - vect2.z));
}
double	dot_product(const t_vec vect1, const t_vec vect2)
{
	return (vect1.x * vect2.x + vect1.y * vect2.y + vect1.z *vect2.z);
}
double	vector_x_cylinder(t_cylinder cy, t_vec r, t_vec o)
{
	t_vec		u;
	t_vec		v;
	double		a1, b1, c1;

	double		a;
	double		b;
	double		c;
	double		t[2];

	//printf("v(%f, %f, %f)\n ", r.x, r.y, r.z);
	u = cross_prod(r, normalize(cy.v));
	v = vec_sub(cy.o, o);
	v = cross_prod(v, normalize(cy.v));
	a = dot_prod(u, u);
	b = 2 * dot_prod(u, v);
	c = dot_prod(v, v) - cy.r2;

	v = multi_vect(cy.v, dot_product(r, cy.v));
	v = sub_vect(r, v);
	u = multi_vect(cy.v, dot_product(sub_vect(o, cy.o), cy.v));
	u = sub_vect(sub_vect(o, cy.o), u);
	a1 = dot_product(v, v);
	b1 = 2 * dot_product(v, u);
	c1 = dot_product(u, u) - pow(cy.radius, 2) * 0.25;
	//if(a != a1 || b != b1 || c != c1)
	//{
	//	printf("r(%f,%f,%f)", r.x, r.y, r.z);
	//	printf("Datos de u: x=%f, y=%f, z=%f | Datos de v: x=%f, y=%f, z=%f | Datos de t_quadratic q: a=%f, b=%f, c=%f\n", u.x, u.y, u.z, v.x, v.y, v.z, a, b, c);
	//	printf("2r(%f,%f,%f)", r.x, r.y, r.z);
	//	printf("Datos de u: x=%f, y=%f, z=%f | Datos de v: x=%f, y=%f, z=%f | Datos de t_quadratic q: a=%f, b=%f, c=%f\n", u.x, u.y, u.z, v.x, v.y, v.z, a1, b1, c1);
	//}

	t[0] = cylinder_covers(cy, r);
	//if (quadratic(a, b, c))
	//	return quadratic(a, b, c);
	//return(0);
	t[1] = cut_cylinder(cy, r, quadratic(a, b, c));
	//return (t[1]);

	if(t[0] || t[1])
		printf("t0 = %f, t1 = %f\n", t[0], t[1]);
	if (t[0] && t[0] < t[1])
		return t[0];
	else if (t[1])
		return t[1];
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
