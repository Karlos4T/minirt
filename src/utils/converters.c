/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:07:30 by dximenez          #+#    #+#             */
/*   Updated: 2024/06/08 15:24:00 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

int	rgb_to_int(char *str)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	split = ft_split(str, ',');
	if (ft_splitlen(split) != 3)
		ft_error("Invalid color format");
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	ft_free_matrix(split);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		ft_error("Invalid color");
	return ((r << 16) | (g << 8) | b);
}

t_vec	str_to_vec(char *str)
{
	char	**split;
	t_vec	v;

	split = ft_split(str, ',');
	if (ft_splitlen(split) != 3)
		ft_error("Invalid vector format");
	v.x = ft_atof(split[0]);
	v.y = ft_atof(split[1]);
	v.z = ft_atof(split[2]);
	ft_free_matrix(split);
	return (v);
}
