/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:34:01 by carlosga          #+#    #+#             */
/*   Updated: 2024/06/06 23:22:50 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	main(int argc, char **argv)
{
	void		*mlx;
	void		*mlx_win;
	t_data		img;
	t_scene		*scene;

	scene = (t_scene *)malloc(sizeof(t_scene));
	if (argc == 2)
		read_rt(argv[1], scene);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "HOLA");
	img.img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.length, &img.endian);
	scene = initialize_scene();
	render_screen(&img, scene);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
