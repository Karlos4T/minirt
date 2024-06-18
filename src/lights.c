/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:13:12 by carlosga          #+#    #+#             */
/*   Updated: 2024/06/09 22:18:54 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	get_brightness_level_sp(t_sphere *s, t_light *l, t_vec *p)
{
	t_vec	v1;
	t_vec	v2;
	double	alpha;

	v1 = normalize(*create_vector(s->o, *p));
	v2 = normalize(*create_vector(l->o, s->o));
	alpha = dot_prod(v1, neg(v2)) / (module(v1) * module(v2));
	if (alpha < 0)
		return (0);
	return (sqrt(alpha));
}

double	get_brightness_level_plane(t_plane *pl, t_light *l, t_vec p)
{
	t_vec	v1;
	double	alpha;

	v1 = normalize(*create_vector(l->o, p));
	alpha = dot_prod(v1, neg(pl->v)) / (module(v1) * module(pl->v));
	if (alpha < 0)
		return (0);
	return (sqrt(alpha));
}

double	get_brightness_level_cylinder(t_cylinder *cy, t_light *l, t_vec p)
{
	t_vec		v1;
	t_vec		v2;
	double		alpha;
	if (cy->is_cover)
	{
		alpha = get_brightness_level_plane(cy->covers[cy->is_cover - 1], l, p);
		cy->is_cover = 0;
		return (alpha);
	}
    t_vec h = vec_sub(cy->o, p);
    double t_proj = dot_prod(h, cy->v);
    t_vec axis_point = vec_add(cy->o, producto_escalar(cy->v, t_proj));
	t_vec oc = vec_sub(cy->o, l->o);
    double projection_length = dot_prod(oc, normalize(cy->v));
    t_vec q = vec_add(cy->o, producto_escalar(normalize(cy->v), projection_length));
    v2 = normalize(vec_sub(q, l->o));
	v1 = normalize(vec_sub(axis_point, p));
	alpha = (dot_prod(v1, v2));
	if ((module(v1) * module(v2)) != 0)
		alpha = alpha / (module(v1) * module(v2));
	return (sqrt(alpha));
}

int	check_shadow(t_vec p, t_vec l, t_objects *ob)
{
	t_vec	v;
	int		i;
	t_ray	*r;

	v = *create_vector(p, l);
	r = malloc(sizeof(t_ray));
	r->o = p;
	r->v = normalize(v);
	i = 0;
	while (ob->sph[i])
	{
		if (vector_x_sphere(ob->sph[i], *r) > 0)
			return (1);
		i++;
	}
	i = 0;
	while (ob->cyl[i])
	{
		if (vector_x_cylinder(ob->cyl[i], *r) < 0)
			return (1);
		i++;
	}
	while (ob->pla[i])
	{
		if (vector_x_plane(ob->pla[i], *r) > 0)
			return (1);
		i++;
	}
	return (0);
}
