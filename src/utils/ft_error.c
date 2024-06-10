/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:54:51 by dximenez          #+#    #+#             */
/*   Updated: 2024/06/08 14:59:06 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

/**
 * @brief Prints "Error: " followed by the message and a newline,
 * then exits the program with status 1.
 */
void	ft_error(char *msg)
{
	printf("Error: %s\n", msg);
	exit(1);
}
