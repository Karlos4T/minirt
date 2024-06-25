/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:33:53 by carlosga          #+#    #+#             */
/*   Updated: 2024/06/25 18:05:44 by dximenez         ###   ########.fr       */
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
	r = *sc.cam->r;
	i = 0;
	while (sc.obj->pla[i] != NULL)
	{
		t = vector_x_plane(sc.obj->pla[i], r);
		if (t && (fabs(t) < fabs(T[0]) || !T[0]) && t < 0)
		{
			T[0] = fabs(t);
			T[1] = 1;
			T[2] = i;
		}
		i++;
	}
	i = 0;
	while (sc.obj->sph[i] != NULL)
	{
		t = vector_x_sphere(sc.obj->sph[i], r);
		if (t && (fabs(t) < fabs(T[0]) || !T[0]))
		{
			T[0] = fabs(t);
			T[1] = 2;
			T[2] = i;
		}
		i++;
	}
	i = 0;
	while (sc.obj->cyl[i] != NULL)
	{
		t = vector_x_cylinder(sc.obj->cyl[i], r);
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

int	*render_plane(t_scene sc, double *T)
{
	t_plane	*pl;
	t_vec	p;
	int		*color;
	double	alpha;

	pl = sc.obj->pla[(int)T[2]];
	p = get_point(*sc.cam->r, T[0]);
	alpha = get_brightness_level_plane(pl, sc.light, p);
	color = calculate_color(sc, pl->color, alpha,
			check_shadow(p, sc.light[0].o, sc.obj));
	return (color);
}

int	*render_sphere(t_scene sc, double *T)
{
	t_sphere	*sp;
	int			*color;
	double		alpha;
	t_vec		p;

	sp = sc.obj->sph[(int)T[2]];
	p = get_point(*sc.cam->r, T[0]);
	alpha = get_brightness_level_sp(sp, sc.light, &p);
	color = calculate_color(sc, sp->color, alpha,
			check_shadow(p, sc.light[0].o, sc.obj));
	return (color);
}

int	*render_cylinder(t_scene sc, double *T)
{
	t_cylinder	*cy;
	double		alpha;
	int			*color;
	t_vec		p;

	cy = sc.obj->cyl[(int)T[2]];
	p = get_point(*sc.cam->r, T[0]);
	alpha = get_brightness_level_cylinder(cy, sc.light, p);
	color = calculate_color(sc, cy->color, alpha,
			check_shadow(p, sc.light[0].o, sc.obj));
	cy->is_cover = 0;
	return (color);
}


void	render_pixel(int x, int y, t_data *data, t_scene sc)
{
	t_ray	*r;
	int		*color;
	double	*T;
	t_vec	*screen_point;

	color = 0;
	r = malloc(sizeof(t_ray));
	screen_point = get_screen_coord(x_pos(x), y_pos(y), sc.cam);
	r->v = vec_sub(sc.cam->o, *screen_point);
	// free(screen_point);		// TODO fix this leak
	r->o = sc.cam->o;
	sc.cam->r = r;

	T = get_closest_object(sc);

	if (T[1] == 1)
		color = render_plane(sc, T);
	else if (T[1] == 2)
	{
		color = render_sphere(sc, T);
	}
	else if (T[1] == 3)
		color = render_cylinder(sc, T);

	free(T);
	free(r);
	my_mlx_pixel_put(data, x, y, hexa(color));
	// free(color);		// TODO fix this leak
}

void render_screen(t_data *data, t_scene *scene)
{
	int i;
	int j;

	i = 0;
	printf("Rendering scene...\n");
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
	printf("Scene rendered Succesfully!\n");
}
