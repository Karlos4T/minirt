/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:54:39 by dximenez          #+#    #+#             */
/*   Updated: 2024/06/06 22:54:11 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minirt.h"
# include "types.h"

typedef enum e_types
{
	ERR=-1,
	AMB,
	CAM,
	LIG,
	SPH,
	PLA,
	CYL
}	t_types;

int			read_rt(char *filename, t_scene *scene);

t_camera	*create_camera(t_vec o, t_vec v, int fov);
t_alight	*create_alight(double intensity, int color);
t_light		*create_light(t_vec o, double intensity, int color);

t_cylinder	*create_cylinder(t_vec o, t_vec v, double diameter, double height, int color);
t_sphere	*create_sphere(t_vec v3, int radius, int color);
t_plane		*create_plane(t_vec o, t_vec v, int color);

#endif