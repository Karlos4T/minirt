/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:18:09 by dximenez          #+#    #+#             */
/*   Updated: 2024/06/25 18:06:28 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static int	on_destroy(t_mlx *vars)
{
	if (vars == NULL)
		exit(0);
	if (vars->mlx && vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
	{
		mlx_loop_end(vars->mlx);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	exit(0);
}

static int	keydown_hook(int keycode, t_mlx *vars)
{
	if (keycode == XK_Escape)
		on_destroy(vars);
	return (0);
}

void	init_hooks(t_mlx *vars)
{
	mlx_hook(vars->win, KeyPress, KeyPressMask, keydown_hook, vars);
	mlx_hook(vars->win, DestroyNotify, StructureNotifyMask, on_destroy, vars);
}
