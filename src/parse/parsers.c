/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:37:55 by dximenez          #+#    #+#             */
/*   Updated: 2024/06/10 18:11:53 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_alight	*parse_ambient(t_scene *scene, char *line)
{
	char	**split;
	double	intensity;
	int		color;

	if (scene->amb != NULL)
		ft_error("Duplicate ambient light");
	split = ft_split(line, ' ');
	if (ft_splitlen(split) != 3)
		ft_error("Invalid ambient light format");
	intensity = ft_atod(split[1]);
	color = rgb_to_int(split[2]);
	ft_free_matrix(split);
	if (intensity < 0 || intensity > 1)
		ft_error("Invalid intensity");
	return (create_alight(intensity, color));
}

t_camera	*parse_cam(t_scene *scene, char *line)
{
	char	**split;
	t_vec	o;
	t_vec	v;
	int		fov;

	if (scene->cam != NULL)
		ft_error("Duplicate camera");
	split = ft_split(line, ' ');
	if (ft_splitlen(split) != 4)
		ft_error("Invalid camera format");
	o = str_to_vec(split[1]);
	v = str_to_vec(split[2]);
	fov = ft_atoi(split[3]);
	ft_free_matrix(split);
	if (!ft_is_normalized(v))
		ft_error("Invalid normalized vector");
	if (fov < 0 || fov > 180)
		ft_error("Invalid fov");
	return (create_camera(o, v, fov));
}

t_light	*parse_light(t_scene *scene, char *line)
{
	char	**split;
	t_vec	o;
	double	intensity;
	int		color;

	if (scene->light != NULL)
		ft_error("Duplicate light");
	split = ft_split(line, ' ');
	if (ft_splitlen(split) != 4)
		ft_error("Invalid light format");
	o = str_to_vec(split[1]);
	intensity = ft_atod(split[2]);
	color = rgb_to_int(split[3]);
	ft_free_matrix(split);
	if (intensity < 0 || intensity > 1)
		ft_error("Invalid intensity");
	return (create_light(o, intensity, color));
}

t_sphere	*parse_sphere(char *line)
{
	char	**split;
	t_vec	v;
	int		diameter;
	int		color;

	split = ft_split(line, ' ');
	if (ft_splitlen(split) != 4)
		ft_error("Invalid sphere format");
	v = str_to_vec(split[1]);
	diameter = ft_atod(split[2]);
	color = rgb_to_int(split[3]);
	ft_free_matrix(split);
	if (diameter < 0)
		ft_error("Invalid shpere diameter");
	return (create_sphere(v, (double) diameter / 2, color));
}

t_plane	*parse_plane(char *line)
{
	char	**split;
	t_vec	o;
	t_vec	v;
	int		color;

	split = ft_split(line, ' ');
	if (ft_splitlen(split) != 4)
		ft_error("Invalid plane format");
	o = str_to_vec(split[1]);
	v = str_to_vec(split[2]);
	color = rgb_to_int(split[3]);
	ft_free_matrix(split);
	if (!ft_is_normalized(v))
		ft_error("Invalid normalized vector");
	return (create_plane(o, v, color));
}

t_cylinder	*parse_cylinder(char *line)
{
	char			**split;
	t_cylinder_p	cy;

	split = ft_split(line, ' ');
	if (ft_splitlen(split) != 6)
		ft_error("Invalid cylinder format");
	cy.o = str_to_vec(split[1]);
	cy.v = str_to_vec(split[2]);
	cy.diameter = ft_atod(split[3]);
	cy.height = ft_atod(split[4]);
	cy.color = rgb_to_int(split[5]);
	ft_free_matrix(split);
	if (cy.diameter < 0 || cy.height < 0)
		ft_error("Invalid cylinder dimensions");
	if (!ft_is_normalized(cy.v))
		ft_error("Invalid normalized vector");
	return (create_cylinder(cy));
}
