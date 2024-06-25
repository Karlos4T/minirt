/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:00:08 by dximenez          #+#    #+#             */
/*   Updated: 2024/06/25 15:53:31 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

static void	print_first(t_scene *s)
{
	if (s->cam != NULL)
	{
		printf("Camera\nOrigin:\t\t%f %f %f\nOrientation:\t%f %f %f\n",
			s->cam->o.x, s->cam->o.y, s->cam->o.z,
			s->cam->v.x, s->cam->v.y, s->cam->v.z);
		printf("FOV:\t\t%f\n\n", s->cam->fov);
	}
	if (s->amb != NULL)
	{
		printf("Ambient light\nBrightness:\t%f\n", s->amb->intensity);
		printf("Color:\t\t%x\n\n", *(s->amb->color));
	}
	if (s->light != NULL)
	{
		printf("Point light\n");
		printf("Origin:\t\t%f %f %f\n", s->light->o.x,
			s->light->o.y, s->light->o.z);
		printf("Brightness:\t%f\n\n", s->light->intensity);
	}
}

static void	print_spheres(t_scene *scene)
{
	int			i;
	t_sphere	**s;
	int			n_sph;

	i = 0;
	s = scene->obj->sph;
	n_sph = scene->obj->n_sph;
	while (i < n_sph)
	{
		printf("Sphere\n");
		printf("Origin:\t\t%f %f %f\n", s[i]->o.x, s[i]->o.y, s[i]->o.z);
		printf("Radius:\t\t%d\n", s[i]->radius);
		printf("Color:\t\t%x\n\n", *(s[i]->color));
		i++;
	}
}

static void	print_planes(t_scene *scene)
{
	int		i;
	t_plane	**p;
	int		n_pla;

	i = 0;
	p = scene->obj->pla;
	n_pla = scene->obj->n_pla;
	while (i < n_pla)
	{
		printf("Plane\n");
		printf("Origin:\t\t%f %f %f\n", p[i]->o.x, p[i]->o.y, p[i]->o.z);
		printf("Normal:\t\t%f %f %f\n", p[i]->v.x, p[i]->v.y, p[i]->v.z);
		printf("Color:\t\t%x\n\n", *(p[i]->color));
		i++;
	}
}

static void	print_cylinders(t_scene *scene)
{
	int			i;
	t_cylinder	**c;
	int			n_cyl;

	i = 0;
	c = scene->obj->cyl;
	n_cyl = scene->obj->n_cyl;
	while (i < n_cyl)
	{
		printf("Cylinder\n");
		printf("Origin:\t\t%f %f %f\n", c[i]->o.x, c[i]->o.y, c[i]->o.z);
		printf("Orientation:\t%f %f %f\n", c[i]->v.x, c[i]->v.y, c[i]->v.z);
		printf("Diameter:\t%f\n", (double) c[i]->radius * 2);
		printf("Height:\t\t%f\n", c[i]->height);
		printf("Color:\t\t%x\n\n", *(c[i]->color));
		i++;
	}

}

void	print_scene(t_scene *scene)
{
	print_first(scene);
	print_spheres(scene);
	print_planes(scene);
	print_cylinders(scene);
}
