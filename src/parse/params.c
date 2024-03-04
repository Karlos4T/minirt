/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:49:39 by carlosga          #+#    #+#             */
/*   Updated: 2024/03/04 17:06:09 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

#define TYPE_PARAMS "NCIRVPF"
/*name, color, intensity, radius, vector, point, fov*/

int is_color(char *c)
{
    char **s;
    int i;

    i = 0;
    s = ft_split(c, ",");
    if (ft_matrix_len(s) != 3)
        return (0);
    while (i < 3)
    {
        if (ft_atoi(s[i]) < 0 || ft_atoi(s[i]) > 255)
            return (0);
        i++;
    }
    return (1);
}

int is_vector(char *c)
{
    char **s;
    int i;

    i = 0;
    s = ft_split(c, ",");
    if (ft_matrix_len(s) != 3)
        return (0);
    while (i < 3)
    {
        if (ft_atoi(s[i]) < 0 || ft_atoi(s[i]) > 1)
            return (0);
        i++;
    }
    return (1);
}