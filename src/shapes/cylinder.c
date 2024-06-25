/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:18:32 by carlosga          #+#    #+#             */
/*   Updated: 2024/06/25 17:01:21 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"


static t_plane	*create_cover(t_cylinder *cy, int color, int type)
{
	t_vec	o;

	if (type == 0)
	{
		o.x = cy->o.x + dot_prod(cy->v, vec_s(1, 0, 0))
			/ (module(cy->v) * module(vec_s(1, 0, 0))) * (cy->height / 2);
		o.y = cy->o.y + dot_prod(cy->v, vec_s(0, 1, 0))
			/ (module(cy->v) * module(vec_s(0, 1, 0))) * (cy->height / 2);
		o.z = cy->o.z + dot_prod(cy->v, vec_s(0, 0, 1))
			/ (module(cy->v) * module(vec_s(0, 0, 1))) * (cy->height / 2);
		return (create_plane(o, cy->v, color));
	}
	else
	{
		o.x = cy->o.x - dot_prod(cy->v, vec_s(1, 0, 0))
			/ (module(cy->v) * module(vec_s(1, 0, 0))) * (cy->height / 2);
		o.y = cy->o.y - dot_prod(cy->v, vec_s(0, 1, 0))
			/ (module(cy->v) * module(vec_s(0, 1, 0))) * (cy->height / 2);
		o.z = cy->o.z - dot_prod(cy->v, vec_s(0, 0, 1))
			/ (module(cy->v) * module(vec_s(0, 0, 1))) * (cy->height / 2);
		return (create_plane(o, neg(cy->v), color));
	}
}

//Esta tiene que ir en math funcs
double map_value(double x)
{
    const double x_min = 1.0;
    const double x_max = 1.75;
    const double y_min = 0.25;
    const double y_max = 0.72;

    return y_min + ((x - x_min) / (x_max - x_min)) * (y_max - y_min);
}


t_cylinder	*create_cylinder(t_cylinder_p cylinder)
{
	t_cylinder	*cy;

	cy = malloc(sizeof(t_cylinder));
	cy->o = cylinder.o;
	cy->v = cylinder.v;
	cy->radius = cylinder.diameter / 2;
	cy->is_cover = 0;
	cy->r2 = cylinder.diameter * cylinder.diameter * map_value(module(cy->v));
	cy->height = cylinder.height;
	cy->covers[0] = create_cover(cy, cylinder.color, 0);
	cy->covers[1] = create_cover(cy, cylinder.color, 1);
	cy->color = rgb(cylinder.color);
	return (cy);
}

int	cut_cylinder(t_cylinder cy, t_ray r, double t)
{
	t_vec	pc;
	t_vec	po;
	double	hip;

	pc = get_point(r, fabs(t));
	po = vec_sub(pc, cy.o);
	hip = module(po);
	if (hip - 1 > sqrt(pow(cy.height / 2, 2) + pow(cy.radius, 2)))
		return (0);
	return (t);
}

double cylinder_covers(t_cylinder *cy, t_ray r)
{
	t_vec		cp;
	int			i;
	double		tp[2];
	
	i = 0;
	while (i < 2)
	{
		tp[i] = vector_x_plane(cy->covers[i], r);
		i++;
	}
	i = 0;
	if(fabs(tp[1]) < fabs(tp[0]))
		i = 1;
	cp = get_point(r, fabs(tp[i]));
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
		return (t[1]);
	}
	else if (t[0])
		return (t[0]);
	return (0);
}