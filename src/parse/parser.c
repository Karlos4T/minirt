/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:45:48 by dximenez          #+#    #+#             */
/*   Updated: 2024/06/06 21:45:49 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_types	get_object_type(char *line)
{
	if (ft_strncmp(line, "A", 2) == 0)
		return (AMB);
	else if (ft_strncmp(line, "C", 2) == 0)
		return (CAM);
	else if (ft_strncmp(line, "L", 2) == 0)
		return (LIG);
	else if (ft_strncmp(line, "sp", 3) == 0)
		return (SPH);
	else if (ft_strncmp(line, "pl", 3) == 0)
		return (PLA);
	else if (ft_strncmp(line, "cy", 3) == 0)
		return (CYL);
	else
		return (ERR);
}

void	parse_line(t_scene *scene, char *line)
{
	if (get_object_type(line) == AMB)
		scene->alight = parse_ambient(line);
	else if (get_object_type(line) == CAM)
		scene->camera = parse_cam(line);
	else if (get_object_type(line) == LIG)
		scene->lights = parse_light(line);
	else if (get_object_type(line) == SPH)
		parse_sphere(line);
	else if (get_object_type(line) == PLA)
		parse_plane(line);
	else if (get_object_type(line) == CYL)
		parse_cylinder(line);
}

void	parse(int fd)
{
	char	*line;
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (scene == NULL)
		return ;
	line = get_next_line(fd);
	while (line != NULL || ft_haschar(line, '\n'))
	{
		parse_line(line, scene);
		free(line);
		line = get_next_line(fd);
	}
}