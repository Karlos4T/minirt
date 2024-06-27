/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:01:58 by dximenez          #+#    #+#             */
/*   Updated: 2024/06/27 14:02:13 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static void	set_values(double **d, double t, double j, double i)
{
	(*d)[0] = t;
	(*d)[1] = j;
	(*d)[2] = i;
}

//_t contiene la siguiente info
//_t[0]: valor de t (distancia del origen al objeto)
//_t[1]: tipo de objeto que se encuentra mas cerca (esfera, cilindro, plano...)
//_t[2]: la posicion del objeto dentro de
//			la array de objetos (esfera 1, esfera 2, cilindro 6...)
double	*get_closest_object(t_scene sc)
{
	const t_ray	r = *sc.cam->r;
	double		*_t;
	int			i;

	_t = malloc(sizeof(double) * 3);
	_t[0] = 0;
	i = -1;
	while (sc.obj->pla[++i] != NULL)
		if (vector_x_plane(sc.obj->pla[i], r)
			&& (!_t[0] || fabs(vector_x_plane(sc.obj->pla[i], r)) < fabs(_t[0]))
			&& vector_x_plane(sc.obj->pla[i], r) < 0)
			set_values(&_t, fabs(vector_x_plane(sc.obj->pla[i], r)), 1, i);
	i = -1;
	while (sc.obj->sph[++i] != NULL)
		if (vector_x_sphere(sc.obj->sph[i], r)
			&& (!_t[0] || fabs(vector_x_sphere(sc.obj->sph[i], r))
				< fabs(_t[0])))
			set_values(&_t, fabs(vector_x_sphere(sc.obj->sph[i], r)), 2, i);
	i = -1;
	while (sc.obj->cyl[++i] != NULL)
		if (vector_x_cylinder(sc.obj->cyl[i], r)
			&& (!_t[0] || fabs(vector_x_cylinder(sc.obj->cyl[i], r))
				< fabs(_t[0])))
			set_values(&_t, fabs(vector_x_cylinder(sc.obj->cyl[i], r)), 3, i);
	return (_t);
}
