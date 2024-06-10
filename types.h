/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:01:02 by dximenez          #+#    #+#             */
/*   Updated: 2024/06/09 22:06:53 by dximenez         ###   ########.fr       */
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

/**
 * @param img Image
 * @param addr Address
 * @param bpp Bits-per-pixel
 * @param length Line length
 * @param endian Endian
 */
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		length;
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
	int		diameter;
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

/**
 * @param cyl Cylinders
 * @param sph Spheres
 * @param pla Planes
 */
typedef struct s_objects
{
	int			n_cyl;
	int			n_sph;
	int			n_pla;
	t_cylinder	*cyl[20];
	t_sphere	*sph[20];
	t_plane		*pla[20];
}	t_objects;

/**
 * @param cam Camera
 * @param obj Objects
 * @param light Point light
 * @param amb Ambient light
 */
typedef struct s_scene
{
	t_camera	*cam;
	t_objects	*obj;
	t_light		*light;
	t_alight	*amb;
}	t_scene;

#endif