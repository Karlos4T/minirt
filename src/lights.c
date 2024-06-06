/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:13:12 by carlosga          #+#    #+#             */
/*   Updated: 2024/06/06 23:15:49 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	get_brightness_level(t_sphere *s, t_light *l, t_vec *p)
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

	v1 = normalize(*create_vector(l->o, p));
	alpha = dot_prod(v1, neg(pl->v)) / (module(v1) * module(pl->v));
	if (alpha < 0)
		return (0);
	return (alpha);
}

double	get_brightness_level_cylinder(t_cylinder *cy, t_light *l, t_vec p)
{
	t_vec		v1;
	t_vec		v2;
	double		alpha;

	if (cy->is_cover)
	{
		return (0.7);
		// TODO check
		alpha = get_brightness_level_plane(cy->covers[cy->is_cover - 1], l, p);
		cy->is_cover = 0;
		return (alpha);
	}
	else
		return (0.6);
	v1 = normalize(*create_vector(cy->o, p));
	v2 = normalize(*create_vector(p, l->o));
	alpha = sqrt(dot_prod(v1, v2) / (module(v1) * module(v2)));
	if (alpha < 0)
		return (0);
	if (alpha > 255)
		printf("alpha: %f", alpha);
	return (alpha);
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
		if (vector_x_sphere(*ob->sph[i], *r))
			return (1);
		i++;
	}
	i = 0;
	while (ob->cyl[i])
	{
		if (vector_x_cylinder(ob->cyl[i], *r))
			return (1);
		i++;
	}
	return (0);
}
