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
		alpha = get_brightness_level_plane(cy->covers[cy->is_cover - 1], l, p);
		cy->is_cover = 0;
		return (alpha);
	}

	//Calcula el punto del eje a la altura del punto de impacto del rayo en el cilindro
    t_vec h = vec_sub(cy->o, p);
    double t_proj = dot_prod(h, cy->v);
    t_vec axis_point = vec_add(cy->o, producto_escalar(cy->v, t_proj));
    
	// Vector perpendicular
    v2 = normalize(vec_sub(p, l->o));
	v1 = normalize(vec_sub(axis_point, p));
	
	alpha = (dot_prod(v1, v2));
	if ((module(v1) * module(v2)) != 0)
		alpha = alpha / (module(v1) * module(v2));
	
	if (alpha == 0)
	{
		printf("ap(%f, %f, %f) --- ", axis_point.x, axis_point.y, axis_point.z);
		printf("p(%f, %f, %f) --- ", p.x, p.y, p.z);
		printf("cyo(%f, %f, %f) --- cyv(%f, %f, %f) --- %f\n", cy->o.x, cy->o.y, cy->o.z, cy->v.x, cy->v.y, cy->v.z, dot_prod(v1, v2));
	}
	//return ((alpha + 1) / 2);
	return (alpha);
	printf("%f, %f\n", dot_prod(v1, v2) / (module(v1)* module(v2)), alpha);
	if (alpha > 1)
		printf("alpha: %f", alpha);

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
		if (vector_x_sphere(ob->sph[i], *r))
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
