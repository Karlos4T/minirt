/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:33:53 by carlosga          #+#    #+#             */
/*   Updated: 2024/04/08 17:13:05 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double *get_closest_object(t_scene sc)
{
	t_ray r;
	double *T;
	double	t;
	int i;
	//T contiene la siguiente info
	//T[0]: valor de t (distancia del origen al objeto)
	//T[1]: tipo de objeto que se encuentra mas cerca (esfera, cilindro, plano...)
	//T[2]: la posicion del objeto dentro de la array de objetos (esfera 1, esfera 2, cilindro 6...)
	
	T = malloc(sizeof(double) * 3);
	r = *sc.camera->r;
	i = 0;
	while (sc.objects->planes[i] != NULL)
	{
		t = vector_x_plane(*sc.objects->planes[i], r);
		if (t && (fabs(t) < fabs(T[0]) || !T[0]) && t < 0)
		{
			T[0] = fabs(t);
			T[1] = 1;
			T[2] = i;
		}
		i++;
	}
	i = 0;
	while (sc.objects->spheres[i] != NULL)
	{
		t = vector_x_sphere(*sc.objects->spheres[i], *sc.camera->r);
		if (t && (fabs(t) < fabs(T[0]) || !T[0]))
		{
			T[0] = fabs(t);
			T[1] = 2;
			T[2] = i;
		}
		i++;
	}
	i = 0;
	while (sc.objects->cylinders[i] != NULL)
	{
		t = vector_x_cylinder(sc.objects->cylinders[i], r);
		if (t && (fabs(t) < fabs(T[0]) || !T[0]))
		{
			T[0] = fabs(t);
			T[1] = 3;
			T[2] = i;
		}
		i++;
	}
	return T;
}

int	render_plane(t_scene sc, double *T)
{
	t_plane *pl = sc.objects->planes[(int)T[2]];
	t_vec p;
	int color;
	double alpha;
	
	p = get_point(*sc.camera->r, T[0]);
	alpha = get_brightness_level_plane(pl, sc.lights, p);
	color = hexa(multiply_colors(pl->color, sc.lights->color, alpha, sc.alight->intensity, check_shadow(p, sc.lights[0].o, sc.objects)));
	return color;
}

int	render_sphere(t_scene sc, double *T)
{
	t_sphere *sp = sc.objects->spheres[(int)T[2]];
	int color;
	double alpha;
	t_vec p;

	p = get_point(*sc.camera->r, T[0]);
	alpha = get_brightness_level(sp, sc.lights, &p);
	color = hexa(multiply_colors(sp->color, sc.lights->color, alpha, sc.alight->intensity, 0)); 
	return color;
}

int render_cylinder(t_scene sc, double *T)
{
	t_cylinder *cy = sc.objects->cylinders[(int)T[2]];
	double alpha;
	int color;
	t_vec p;

	p = get_point(*sc.camera->r, T[0]);
	alpha = get_brightness_level_cylinder(cy, sc.lights, p);
	(void)color;
	color = hexa(multiply_colors(cy->color, sc.lights->color, alpha, sc.alight->intensity, 0));
	cy->is_cover = 0;
	return color;
}


void render_pixel(int x, int y, t_data *data, t_scene sc)
{
	t_ray *r;
	int color = 0;
	double *T;
	t_vec	*screen_point;
	
	r = malloc(sizeof(t_ray));
	screen_point = get_screen_coord(x_pos(x), y_pos(y), sc.camera);
	r->v = vec_sub(sc.camera->o, *screen_point);
	r->o = sc.camera->o;
	sc.camera->r = r;
	
	T = get_closest_object(sc);

	if (T[1] == 1)
		color = render_plane(sc, T);
	else if (T[1] == 2)
		color = render_sphere(sc, T);
	else if (T[1] == 3)
		color = render_cylinder(sc, T);
	free(T);
	my_mlx_pixel_put(data, x, y, color);
}

void render_screen(t_data *data, t_scene *scene)
{
	int i;
	int j;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			render_pixel(j, i, data, *scene);
			j++;
		}
		i++;
	}
}
