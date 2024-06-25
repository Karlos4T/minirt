/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:05:41 by dximenez          #+#    #+#             */
/*   Updated: 2024/06/25 18:04:44 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIN_WIDTH 1440
# define WIN_HEIGHT 1080
# define M_PI 3.141592

# include "parse.h"
# include "types.h"

# include "./mlx-linux/mlx.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include "./libft/include/libft.h"

# include <X11/X.h>
# include <X11/keysym.h>


//FUNCTIONS
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);

t_vec		*create_vector(t_vec point1, t_vec point2);
double		vector_x_sphere(t_sphere *s, t_ray r);
double		vector_x_plane(t_plane *pl, t_ray r);
void		render_screen(t_data *data, t_scene *scene);
double		vector_x_cylinder(t_cylinder *cy, t_ray r);

//UTILS
int			ft_haschar(char *s, char c);
int			ft_splitlen(char **split);
void		ft_error(char *s);
int			rgb_to_int(char *str);
t_vec		str_to_vec(char *str);
int			ft_is_normalized(t_vec v);
void		print_scene(t_scene *scene);
int			ft_is_empty(char *line);
double		ft_atod(char *s);

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
t_vec		vec_s(double x, double y, double z);
t_vec		cross_prod(t_vec v1, t_vec v2);
t_vec		vec_sub(t_vec a, t_vec b);
int			check_shadow(t_vec p, t_vec l, t_objects *ob);
double		quadratic(double a, double b, double c);
t_vec		vec_add(t_vec v1, t_vec v2);
t_vec		producto_escalar(t_vec v, double n);
t_vec		get_point(t_ray r, int t);

//COLOR
double		get_brightness_level_sp(t_sphere *s, t_light *l, t_vec *p);
double		get_brightness_level_plane(t_plane *s, t_light *l, t_vec p);
double		get_brightness_level_cylinder(t_cylinder *c, t_light *l, t_vec p);
int			*calculate_color(t_scene sc, int *surface_color, float alpha, int is_shadow);

//MAIN
void		render_pixel(int x, int y, t_data *data, t_scene scene);
t_vec		*get_screen_coord(int x, int y, t_camera *c);
t_scene		*initialize_scene();

//HOOKS
void		init_hooks(t_mlx *mlx);

#endif