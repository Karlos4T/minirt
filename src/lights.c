/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:13:12 by carlosga          #+#    #+#             */
/*   Updated: 2024/03/15 12:54:44 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double get_brightness_level(t_sphere *s, t_light *l, t_vec *p)
{
	t_vec	v1;
	t_vec	v2;
	double		alpha;

	/*---- NO CAMBIAR ESTE BLOQUE ----*/
	//v1 = *create_vector(*p, s->o);
	/*v1 = create_vector(l->o, *p);
	v2 = create_vector(l->o, s->o);
	alpha = module(*v1) - module(*v3) + s->radius;
	alpha = (1 - (alpha / s->radius)) * l->intensity;*/
	/*--------------------------------*/

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
	//t_vector	v2;
	double		alpha;

	v1 = normalize(*create_vector(l->o, *p));
	alpha = dot_prod(v1, neg(pl->v)) / (module(v1) * module(pl->v));

	//printf("v1(%f, %f, %f) %f\n", v1.x, v1.y, v1.z, alpha);
	if (alpha < 0)
		return (0);
	return (alpha);
}

double	get_brightness_level_cylinder(t_cylinder *cy, t_light *l, t_vec *p)
{
	t_vec	    v1;
	t_vec	    v2;
	double		alpha;

	v1 = normalize(*create_vector(cy->o, *p));
	v2 = normalize(*create_vector(l->o, cy->o));
	alpha = dot_prod(v1, neg(v2)) / (module(v1) * module(v2));
	//printf("alpha : %f\n", alpha);
    if (alpha < 0)
		return (0);

	//free(v1);
	return (alpha);
}


int check_shadow(t_vec p, t_vec l, t_sphere **s)
{
	t_vec 	v;
	int		i;

	i = 0;
	//v = normalize(*create_vector(p, l));
	v = *create_vector(p, l);
	while (s[i])
	{
		if (vector_x_sphere(*s[i], v, p))
		{	
			return (1);
		}
		i++;
	}
	return (0);
}