/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:44:53 by carlosga          #+#    #+#             */
/*   Updated: 2024/04/05 13:37:08 by carlosga         ###   ########.fr       */
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

t_vec get_point(t_ray r, int t)
{
	t_vec v;
	
	v.x = r.o.x + r.v.x * t;
	v.y = r.o.y + r.v.y * t;
	v.z = r.o.z + r.v.z * t;
	return v;
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

t_vec	cross_prod(t_vec u, t_vec v)
{
	t_vec	dst;

	dst.x = u.y * v.z - u.z * v.y;
	dst.y = u.z * v.x - u.x * v.z;
	dst.z = u.x * v.y - u.y * v.x;
	return (dst);
}

t_vec	vec_add(t_vec v1, t_vec v2)
{
	v1.x = v1.x + v2.x;
	v1.y = v1.y + v2.y;
	v1.z = v1.z + v2.z;
	return(v1);
}

t_vec	vec_sub(t_vec v1, t_vec v2)
{
	t_vec	v;
	
	v.x = v2.x - v1.x;
	v.y = v2.y - v1.y;
	v.z = v2.z - v1.z;
	return (v);
}

double dot_prod(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double quadratic(double a, double b, double c)
{
	double D;
	double t[2];

	D = b * b - (4 * a * c);
	if (D >= 0)
	{
		//printf("v(%f, %f, %f) D = %f\n", v.x, v.y, v.z, D);
		t[0] = (- b + sqrt(D)) / (2 * a);
		t[1] = (- b - sqrt(D)) / (2 * a);
		if (fabs(t[0]) < fabs(t[1]))
			return (fabs(t[0]));
		return (fabs(t[1]));
	}
	return (0);
}

t_vec *get_screen_coord(int x, int y, t_camera *c)
{
	t_vec	*coords;
	coords = malloc(sizeof(t_vec));

	double wsize;
	wsize = fabs(tan(c->fov/2));
	
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
