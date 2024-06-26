/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_normalized.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:42:07 by dximenez          #+#    #+#             */
/*   Updated: 2024/06/10 18:09:01 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

int	ft_is_normalized(t_vec v)
{
	return (v.x >= -1 && v.x <= 1
		&& v.y >= -1 && v.y <= 1
		&& v.z >= -1 && v.z <= 1);
}
