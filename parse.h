/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:54:39 by dximenez          #+#    #+#             */
/*   Updated: 2024/06/27 14:15:03 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minirt.h"
# include "types.h"

typedef enum e_types
{
	CMT=-2,
	ERR=-1,
	AMB,
	CAM,
	LIG,
	SPH,
	PLA,
	CYL
}	t_types;

typedef struct s_cylinder_p
{
	t_vec	o;
	t_vec	v;
	double	diameter;
	double	height;
	int		color;
}	t_cylinder_p;

void		open_rt(char *filename, t_scene *scene);
void		parse(int fd, t_scene *scene);

t_camera	*create_camera(t_vec o, t_vec v, int fov);
t_alight	*create_alight(double intensity, int color);
t_light		*create_light(t_vec o, double intensity, int color);

t_cylinder	*create_cylinder(t_cylinder_p cylinder);
t_sphere	*create_sphere(t_vec v3, int radius, int color);
t_plane		*create_plane(t_vec o, t_vec v, int color);

//PARSERS
t_alight	*parse_ambient(t_scene *scene, char *line);
t_camera	*parse_cam(t_scene *scene, char *line);
t_light		*parse_light(t_scene *scene, char *line);

t_sphere	*parse_sphere(char *line);
t_plane		*parse_plane(char *line);
t_cylinder	*parse_cylinder(char *line);

#endif