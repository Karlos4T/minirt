/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:05:41 by dximenez          #+#    #+#             */
/*   Updated: 2024/06/06 22:07:19 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIN_WIDTH 1440
# define WIN_HEIGHT 1080

# include "parse.h"
# include "types.h"

# include "./mlx-linux/mlx.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include "./libft/include/libft.h"


//FUNCTIONS
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_sphere	*create_sphere(int x, int y, int z, int radius, int color);
t_vec		*create_vector(t_vec point1, t_vec point2);
double		vector_x_sphere(t_sphere s, t_ray r);
double		vector_x_plane(t_plane pl, t_ray r);
void		render_screen(t_data *data, t_scene *scene);
t_vec		*create_point(int x, int y, int z);
t_light		*create_light(int x, int y, int z, double intensity, int color);
t_camera	*start_camera(double x, double y, double z, double vx, double vy, double vz, int fov);
t_plane		*create_plane(int x, int y, int z, double vx, double vy, double vz, int color);
t_alight	*create_alight(double intensity, int color);
t_cylinder	*create_cylinder(int x, int y, int z, double vx, double vy, double vz, double radius, double height, int color);
double		vector_x_cylinder(t_cylinder *cy, t_ray r);

//MATH FUNCTIONS
int			x_pos(int x);
int			y_pos(int y);
int			hexa(int *rgb);
int			*rgb(int color);
double		module(t_vec v);
t_vec		normalize(t_vec v);
double		dot_prod(t_vec v1, t_vec v2);
t_vec		neg(t_vec v);
t_vec		*vec(double x, double y, double z);
t_vec		cross_prod(t_vec v1, t_vec v2);
t_vec		vec_sub(t_vec a, t_vec b);
int			check_shadow(t_vec p, t_vec l, t_objects *ob);
double		quadratic(double a, double b, double c);
t_vec		vec_add(t_vec v1, t_vec v2);
t_vec		producto_escalar(t_vec v, double n);
t_vec		get_point(t_ray r, int t);


//COLOR
int 		*multiply_colors(int *rgb1, int *rgb2, double alpha, double al, int is_shadow);
double		get_brightness_level(t_sphere *s, t_light *l, t_vec *p);
double		get_brightness_level_plane(t_plane *s, t_light *l, t_vec p);
double		get_brightness_level_cylinder(t_cylinder *c, t_light *l, t_vec p);


//MAIN
void		render_pixel(int x, int y, t_data *data, t_scene scene);
t_vec		*get_screen_coord(int x, int y, t_camera *camera);
t_scene		*initialize_scene();




#endif