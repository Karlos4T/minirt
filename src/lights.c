/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:13:12 by carlosga          #+#    #+#             */
/*   Updated: 2024/06/25 18:11:50 by dximenez         ###   ########.fr       */
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
	return (alpha);
}

double	get_brightness_level_plane(t_plane *pl, t_light *l, t_vec p)
{
	t_vec	v1;
	double	alpha;
	t_vec	*v;

	v = create_vector(l->o, p);
	v1 = normalize(*v);
	free(v);
	alpha = dot_prod(v1, neg(pl->v)) / (module(v1) * module(pl->v));
	if (alpha < 0)
		return (0);
	return (alpha * alpha);
}

double	get_brightness_level_cylinder(t_cylinder *cy, t_light *l, t_vec p)
{
	t_vec	v1;
	t_vec	v2;
	double	alpha;
	t_vec	axis_point;
	t_vec	q;

	axis_point = vec_add(cy->o, producto_escalar(cy->v,
				dot_prod(vec_sub(cy->o, p), cy->v)));
	q = vec_add(cy->o, producto_escalar(normalize(cy->v),
				dot_prod(vec_sub(cy->o, l->o), normalize(cy->v))));
	if (cy->is_cover)
	{
		alpha = get_brightness_level_plane(cy->covers[cy->is_cover - 1], l, p);
		cy->is_cover = 0;
		return (alpha);
	}
	v2 = normalize(vec_sub(q, l->o));
	v1 = normalize(vec_sub(axis_point, p));
	alpha = (dot_prod(v1, v2));
	if ((module(v1) * module(v2)) != 0)
		alpha = alpha / (module(v1) * module(v2));
	return (sqrt(alpha));
}

int	check_shadow(t_vec p, t_vec l, t_objects *ob)
{
	t_vec	*v;
	int		i;
	t_ray	*r;

	v = create_vector(p, l);
	r = malloc(sizeof(t_ray));
	r->o = p;
	r->v = normalize(*v);
	free(v);
	i = -1;
	while (ob->sph[++i])
		if (vector_x_sphere(ob->sph[i], *r) > 0)
			return (free(r), 1);
	i = -1;
	while (ob->cyl[++i])
		if (vector_x_cylinder(ob->cyl[i], *r) < 0)
			return (free(r), 1);
	return (free(r), 0);
}
