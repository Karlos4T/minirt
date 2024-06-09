/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:16:53 by dximenez          #+#    #+#             */
/*   Updated: 2024/06/08 15:51:16 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

static int	check_format(char *f)
{
	int	len;

	len = ft_strlen(f);
	if (f[len - 3] == '.' && f[len - 2] == 'r' && f[len - 1] == 't')
		return (1);
	return (0);
}

void	open_rt(char *filename, t_scene *scene)
{
	int	fd;

	if (!check_format(filename))
		ft_error("Invalid file format (must end in .rt)");
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_error("Invalid file");
	scene->obj = malloc(sizeof(t_objects));
	if (scene->obj == NULL)
		ft_error("Malloc error");
	scene->obj->n_sph = 0;
	scene->obj->n_pla = 0;
	scene->obj->n_cyl = 0;
	parse(fd, scene);
}
