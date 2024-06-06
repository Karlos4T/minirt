/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:54:39 by dximenez          #+#    #+#             */
/*   Updated: 2024/06/06 22:01:55 by dximenez         ###   ########.fr       */
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

int	read_rt(char *filename, t_scene *scene);

#endif