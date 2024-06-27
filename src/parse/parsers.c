/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:37:55 by dximenez          #+#    #+#             */
/*   Updated: 2024/06/27 14:06:19 by dximenez         ###   ########.fr       */
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
	v.x = -v.x;
	fov = ft_atoi(split[3]);
	if (fov == 180)
		fov = 179;
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
