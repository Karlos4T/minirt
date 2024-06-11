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

	//Calcula el rayo perpendicular al eje del cilindro que cruza con el origen del rayo
    t_vec oc = vec_sub(cy->o, l->o);
    double projection_length = dot_prod(oc, normalize(cy->v));
    t_vec q = vec_add(cy->o, producto_escalar(normalize(cy->v), projection_length));

    // Vector perpendicular
    v2 = normalize(vec_sub(l->o, q));
	v1 = normalize(*create_vector(axis_point, p));
	
	//printf("v1(%f, %f, %f) --- v2(%f, %f, %f) --- %f\n", v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, dot_prod(v1, v2));
	double d = dot_prod(v1, neg(v2)) / (module(v1) * module(v2));
	if (d < 0)
		return 0;
	alpha = sqrt(d);
	printf("%f, %f\n", dot_prod(v1, v2) / (module(v1)* module(v2)), alpha);
	if (alpha < 0)
		return (0);
	if (alpha > 1)
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
