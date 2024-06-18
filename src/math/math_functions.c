/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:44:53 by carlosga          #+#    #+#             */
/*   Updated: 2024/04/05 17:30:45 by carlosga         ###   ########.fr       */
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
	double m = module(v);
	if (m == 0)
		m = 0.1;

	v.x = v.x / m;
	v.y = v.y / m;
	v.z = v.z / m;
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
		t[0] = (- b + sqrt(D)) / (2 * a);
		t[1] = (- b - sqrt(D)) / (2 * a);
		if (fabs(t[0]) < fabs(t[1]))
			return (t[0]);
		return (t[1]);
	}
	return (0);
}

t_vec *get_screen_coord(int x, int y, t_camera *c)
{
    t_vec *coords;
    double wsize;

    coords = malloc(sizeof(t_vec));
    if (!coords)
        return NULL;

    t_vec global_up = {0.0f, 1.0f, 0.0f};

    t_vec right = normalize(cross_prod(global_up, c->v));

    t_vec up = normalize(cross_prod(c->v, right));

    wsize = fabs(tan(c->fov / 2));

    float screen_x = x * wsize / WIN_HEIGHT;
    float screen_y = y * wsize / WIN_HEIGHT;

    coords->x = c->o.x - screen_x * right.x - screen_y * up.x - c->v.x;
    coords->y = c->o.y + screen_x * right.y + screen_y * up.y + c->v.y;
    coords->z = c->o.z + screen_x * right.z + screen_y * up.z + c->v.z;
    
    return coords;
}
