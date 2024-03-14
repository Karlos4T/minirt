/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:44:53 by carlosga          #+#    #+#             */
/*   Updated: 2024/03/14 15:12:45 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

int x_pos(int x)
{
    return (x + WIN_WIDTH / 2 - WIN_WIDTH);
}

int y_pos(int y)
{
    return (-y - WIN_HEIGHT / 2 + WIN_HEIGHT);
}

double module(t_vec v)
{
	return(sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec producto_escalar(t_vec v, double n)
{
	v.x = v.x * n;
	v.y = v.y * n;
	v.z = v.z * n;
	return (v);
}

t_vec normalize(t_vec v)
{
	v.x = v.x / module(v);
	v.y = v.y / module(v);
	v.z = v.z / module(v);
	return(v);
}

t_vec neg(t_vec v)
{
	v.x = -v.x;
	v.y = -v.y;
	v.z = -v.z;
	return (v);
}

t_vec *cross(t_vec v1, t_vec v2)
{
	t_vec *v;
	v = malloc(sizeof(t_vec));

	v->x = v1.x * v2.x + v1.x * v2.y + v1.x * v2.z / (module(v1) * module(v2));
	v->y = v1.y * v2.x + v1.y * v2.y + v1.y * v2.z / (module(v1) * module(v2));
	v->z = v1.z * v2.x + v1.z * v2.y + v1.z * v2.z / (module(v1) * module(v2));
	return (v);
}

double dot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec *get_screen_coord(int x, int y, t_camera *c)
{
	t_vec	*coords;
	t_vec *center = vec(c->o.x + c->v.x, c->o.y + c->v.y, c->o.z + c->v.z);
	t_vec *up = vec(0, 1, 0);
	t_vec *horz = cross(*up, c->v);
	t_vec *vert = cross(c->v, *horz);
	double wsize;
	(void)x;
	(void)y;
	wsize = fabs(tan(c->fov/2));
	coords = malloc(sizeof(t_vec));
	
	t_vec *origin;
	origin = malloc(sizeof(t_vec));
	origin->x = center->x - (((WIN_WIDTH - 1) / 2) * (wsize / WIN_HEIGHT) * horz->x)+ (((WIN_HEIGHT - 1) / 2) * (wsize / WIN_HEIGHT) * vert->x);
	origin->y = center->y - (((WIN_WIDTH - 1) / 2) * (wsize / WIN_HEIGHT) * horz->y)+ (((WIN_HEIGHT - 1) / 2) * (wsize / WIN_HEIGHT) * vert->y);
	origin->z = center->z - (((WIN_WIDTH - 1) / 2) * (wsize / WIN_HEIGHT) * horz->z)+ (((WIN_HEIGHT - 1) / 2) * (wsize / WIN_HEIGHT) * vert->z);
	
	t_vec *pixl;
	pixl = malloc(sizeof(t_vec));
	pixl->x = origin->x + (x * wsize / WIN_HEIGHT * horz->x) - (y * wsize / WIN_HEIGHT * vert->x);
	pixl->y = origin->y + (x * wsize / WIN_HEIGHT * horz->y) - (y * wsize / WIN_HEIGHT * vert->y);
	pixl->z = origin->z + (x * wsize / WIN_HEIGHT * horz->z) - (y * wsize / WIN_HEIGHT * vert->z);

	coords->x = c->o.x + ((pixl->x - c->o.x) / fabs(pixl->x - c->o.x)) * -1;
	coords->y = c->o.y + ((pixl->y - c->o.y) / fabs(pixl->y - c->o.y)) * -1;
	coords->y = c->o.z + ((pixl->z - c->o.z) / fabs(pixl->z - c->o.z)) * -1;

	//printf("%f\n", x * limit / WIN_HEIGHT);
	/*
		LOS PUNTOS X E Y QUE RECIBIMOS NO SON LOS MISMOS PUNTOS EN EL PLANO 3D
		ES DECIR TIENEN COMPONENTES EN x, y, z.
		EL PUNTO XY DE LA PANTALLA ES EL PUNTO xyz del plano
	*/
	
	coords->x = x * wsize / WIN_HEIGHT + c->o.x + c->v.x;
	coords->y = y * wsize / WIN_HEIGHT + c->o.y + c->v.y;
	coords->z = c->o.z - 1;
	
	//printf("v(%f, %f, %f)\n", coords->x, coords->y, coords->z);
	return(coords);
}
