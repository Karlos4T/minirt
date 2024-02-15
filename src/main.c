/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:34:01 by carlosga          #+#    #+#             */
/*   Updated: 2024/02/15 17:58:47 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"






t_camera *start_camera(int x, int y, int z, int fov)
{
	t_camera	*camera;
	t_cords	*cords;

	camera = malloc(sizeof(t_camera));
	cords = malloc(sizeof(t_cords));
	cords->x = x;
	cords->y = y;
	cords->z = z;
	camera->cords = cords;
	camera->fov = fov;

	return camera;
}

double get_brightness_level(t_sphere *s, t_light *l, t_cords *p)
{
	t_vector *v1;
	t_vector *v2;
	double	alpha;
	
	v1 = create_vector(*p, l->o);
	v2 = create_vector(s->o, l->o);
	
	alpha = 1 / cos(v1->x * v2->x + v1->y * v2->y + v1->z * v2->z / (module(*v1) * module(*v2)));
	alpha = alpha * 180 / 3.1416;
	//if (alpha  == 0.0)
	return (alpha);
}


void render_pixel(int x, int y, t_data *data)
{
	t_cords		*screen_point;
	t_cords		*origin;
	t_vector	*vector;
	t_sphere	*sphere;
	t_light		*light;
	int color = 0X000000;
	int	t;
	double	alpha;

	sphere = create_sphere(0, 0, -90, 8, 0xFFFFFF);
	light = create_light(0, -100, -90, 5, 0xFFFFFF);
	origin = create_point(0, 0, 0);
	screen_point = get_screen_coord(x_pos(x), y_pos(y), 70);
	vector = create_vector(*screen_point, *origin);
	t = vector_x_sphere(*sphere, *vector);
	if (t)
	{
		//Calcular Nivel de luminosidad del pixel y color
		double alpha = get_brightness_level(sphere, light, create_point(0 + t * (screen_point->x - 0),  0 + t * (screen_point->y - 0), 0 + t * (screen_point->z - 0)));
		int rgb[] = {(int)alpha, (int)alpha, (int)alpha};
		color = hexa(rgb);
		if (color != 0)
			printf("%x\n", color);
		//color = 0xFFFFFF;
	}
	my_mlx_pixel_put(data, x, y, color);
}


int main()
{
	void		*mlx;
	void		*mlx_win;
	t_data		img;
	t_camera	*camera;

	camera = start_camera(0, 0, 0, 90);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIN_HEIGHT, WIN_WIDTH, "HOLA");
	img.img = mlx_new_image(mlx, WIN_HEIGHT, WIN_WIDTH);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	render_screen(&img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
