/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:33:53 by carlosga          #+#    #+#             */
/*   Updated: 2024/06/27 14:24:53 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	render_plane(t_scene sc, double *T)
{
	t_plane	*pl;
	t_vec	p;
	int		color;
	double	alpha;

	pl = sc.obj->pla[(int)T[2]];
	p = get_point(*sc.cam->r, T[0]);
	alpha = get_brightness_level_plane(pl, sc.light, p);
	color = calculate_color(sc, pl->color, alpha,
			check_shadow(p, sc.light[0].o, sc.obj));
	return (color);
}

int	render_sphere(t_scene sc, double *T)
{
	t_sphere	*sp;
	int			color;
	double		alpha;
	t_vec		p;

	sp = sc.obj->sph[(int)T[2]];
	p = get_point(*sc.cam->r, T[0]);
	alpha = get_brightness_level_sp(sp, sc.light, &p);
	color = calculate_color(sc, sp->color, alpha,
			check_shadow(p, sc.light[0].o, sc.obj));
	return (color);
}

int	render_cylinder(t_scene sc, double *T)
{
	t_cylinder	*cy;
	double		alpha;
	int			color;
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
	int		color;
	double	*t;
	t_vec	*coords;

	color = 0;
	r = malloc(sizeof(t_ray));
	coords = get_screen_coord(x_pos(x), y_pos(y), sc.cam);
	r->v = vec_sub(sc.cam->o, *coords);
	free(coords);
	r->o = sc.cam->o;
	sc.cam->r = r;
	t = get_closest_object(sc);
	if (t[1] == 1)
		color = render_plane(sc, t);
	else if (t[1] == 2)
	{
		color = render_sphere(sc, t);
	}
	else if (t[1] == 3)
		color = render_cylinder(sc, t);
	free(t);
	free(r);
	my_mlx_pixel_put(data, x, y, color);
}

void	render_screen(t_data *data, t_scene *scene)
{
	int	i;
	int	j;

	i = 0;
	if (!scene->amb || !scene->cam || !scene->light)
		ft_error("Missing scene elements");
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
