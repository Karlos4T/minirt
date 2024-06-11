/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:45:48 by dximenez          #+#    #+#             */
/*   Updated: 2024/06/11 16:01:17 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

static t_types	get_object_type(char *line)
{
	if (ft_strncmp(line, "A ", 2) == 0)
		return (AMB);
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (CAM);
	else if (ft_strncmp(line, "L ", 2) == 0)
		return (LIG);
	else if (ft_strncmp(line, "sp ", 3) == 0)
		return (SPH);
	else if (ft_strncmp(line, "pl ", 3) == 0)
		return (PLA);
	else if (ft_strncmp(line, "cy ", 3) == 0)
		return (CYL);
	else if (ft_strncmp(line, "#", 1) == 0)
		return (CMT);
	else
		return (ERR);
}

void	parse_line(t_scene *scene, char *line)
{
	if (get_object_type(line) == AMB)
		scene->amb = parse_ambient(scene, line);
	else if (get_object_type(line) == CAM)
		scene->cam = parse_cam(scene, line);
	else if (get_object_type(line) == LIG)
		scene->light = parse_light(scene, line);
	else if (get_object_type(line) == SPH)
	{
		scene->obj->sph[(scene->obj->n_sph)++] = parse_sphere(line);
		scene->obj->sph[scene->obj->n_sph] = NULL;
	}
	else if (get_object_type(line) == PLA)
	{
		scene->obj->pla[(scene->obj->n_pla)++] = parse_plane(line);
		scene->obj->pla[scene->obj->n_pla] = NULL;
	}
	else if (get_object_type(line) == CYL)
	{
		scene->obj->cyl[(scene->obj->n_cyl)++] = parse_cylinder(line);
		scene->obj->cyl[scene->obj->n_cyl] = NULL;
	}
	else if (get_object_type(line) == ERR)
		ft_error("Invalid object type");
}

void	parse(int fd, t_scene *scene)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL || ft_haschar(line, '\n'))
	{
		if (!ft_is_empty(line))
			parse_line(scene, line);
		free(line);
		line = get_next_line(fd);
	}
}
