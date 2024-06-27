/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:06:23 by dximenez          #+#    #+#             */
/*   Updated: 2024/06/27 14:06:31 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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
