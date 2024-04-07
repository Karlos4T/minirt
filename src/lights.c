/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:13:12 by carlosga          #+#    #+#             */
/*   Updated: 2024/04/07 12:36:56 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double get_brightness_level(t_sphere *s, t_light *l, t_vec *p)
{
	t_vec	v1;
	t_vec	v2;
	double		alpha;

	v1 = normalize(*create_vector(s->o, *p));
	v2 = normalize(*create_vector(l->o, s->o));
	alpha = dot_prod(v1, neg(v2)) / (module(v1) * module(v2));
	if (alpha < 0)
		return (0);
	return (alpha);
}

double get_brightness_level_plane(t_plane *pl, t_light *l, t_vec *p)
{
	t_vec	v1;
	double		alpha;

	v1 = normalize(*create_vector(l->o, *p));
	alpha = dot_prod(v1, neg(pl->v)) / (module(v1) * module(pl->v));
	if (alpha < 0)
		return (0);
	return (alpha);
}

double	get_brightness_level_cylinder(t_cylinder *cy, t_light *l, t_vec *p)
{
	t_vec		v1;
	t_vec		v2;
	double		alpha;
	
	if (cy->is_cover)
	{
		return(0.7);

		alpha = get_brightness_level_plane(cy->covers[cy->is_cover - 1], l, p);
		cy->is_cover = 0;
		return (alpha);
	}
	else
		return(0.6);
	v1 = normalize(*create_vector(cy->o, *p));
	v2 = normalize(*create_vector(*p, l->o));
	alpha = sqrt(dot_prod(v1, v2) / (module(v1) * module(v2)));
	if (alpha < 0)
		return (0);
	if (alpha > 255)
		printf("alpha: %f", alpha);
	return (alpha);
}

int check_shadow(t_vec p, t_vec l, t_objects *ob)
{
	t_vec	v;
	int		i;
	t_ray	*r;

	v = *create_vector(p, l);
	r = malloc(sizeof(t_ray));
	r->o = p;
	r->v = normalize(v);
	
	i = 0;
	while (ob->spheres[i])
	{
		if (vector_x_sphere(*ob->spheres[i], *r))
			return (1);
		i++;
	}
	i = 0;
	while (ob->cylinders[i])
	{
		if (vector_x_cylinder(ob->cylinders[i], *r))
			return (1);
		i++;
	}
	return (0);
}
