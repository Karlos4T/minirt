/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:01:02 by dximenez          #+#    #+#             */
/*   Updated: 2024/06/06 22:01:40 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_ray
{
	t_vec	o;
	t_vec	v;
}	t_ray;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_camera
{
	t_vec	o;
	t_vec	v;
	t_ray	*r;
	int		fov;
}	t_camera;

typedef struct s_sphere
{
	t_vec	o;
	int		radius;
	int		*color;
}	t_sphere;

typedef struct s_plane
{
	t_vec	o;
	t_vec	v;
	int		*color;
}	t_plane;

typedef struct s_cylinder
{
	t_vec		o;
	t_vec		v;
	double		radius;
	double		r2;
	double		height;
	int			*color;
	int			is_cover;
	t_plane		*covers[2];
}	t_cylinder;

typedef struct s_light
{
	t_vec	o;
	int		x_origin;
	int		y_origin;
	int		z_origin;
	double	intensity;
	int		*color;
}	t_light;

typedef struct s_alight
{
	double	intensity;
	int		*color;
}	t_alight;

typedef struct s_objects
{
	t_cylinder	**cylinders;
	t_sphere	**spheres;
	t_plane		**planes;
}	t_objects;

typedef struct s_scene
{
	t_camera	*camera;
	t_objects	*objects;
	t_light		*lights;
	t_alight	*alight;
}	t_scene;

#endif