/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:34:01 by carlosga          #+#    #+#             */
/*   Updated: 2024/06/26 16:16:05 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static void	init_window(t_mlx *mlx, t_data *i)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "MiniRT");
	i->img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	i->addr = mlx_get_data_addr(i->img, &i->bpp, &i->length, &i->endian);
}

int	main(int argc, char **argv)
{
	t_mlx		mlx;
	t_scene		*scene;

	scene = (t_scene *)malloc(sizeof(t_scene));
	if (argc != 2)
		(printf("Error: no argument\n"), exit(1));
	open_rt(argv[1], scene);
	print_scene(scene);
	init_window(&mlx, &mlx.img);
	init_hooks(&mlx);
	render_screen(&mlx.img, scene);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
	mlx_loop(mlx.mlx);
	return (0);
}
