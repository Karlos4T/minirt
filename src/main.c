/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user4t <user4t@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:34:01 by carlosga          #+#    #+#             */
/*   Updated: 2024/02/18 21:51:05 by user4t           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void print_light(t_data *data, t_scene *scene)
{
	t_cords o;

	o = scene->lights->o;
	my_mlx_pixel_put(data, x_pos(o.x), y_pos(o.y), 0xFFFFFF);
}

t_camera *start_camera(int x, int y, int z, int fov)
{
	t_camera	*camera;
	t_cords		*cords;

	camera = malloc(sizeof(t_camera));
	cords = malloc(sizeof(t_cords));
	cords->x = x;
	cords->y = y;
	cords->z = z;
	camera->o = cords;
	camera->fov = fov;

	return camera;
}

double get_brightness_level(t_sphere *s, t_light *l, t_cords *p)
{
	t_vector *v1;
	t_vector *v2;
	double	alpha;
	
	v1 = create_vector(s->o, *p);
	v2 = create_vector(s->o, l->o);
	
	alpha = v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
	alpha = 255 - 50 * alpha / 255;
	//printf("%f\n", alpha);
	//alpha = alpha * 180 / 3.1416;
	//if (alpha  == 0.0)
	return (alpha);
}


void render_pixel(int x, int y, t_data *data, t_scene sc)
{
	t_cords		*screen_point;
	t_vector	*vector;
	int color = 0X000000;
	int	t;
	int i;
	double	alpha;
	int		*colors;

	screen_point = get_screen_coord(x_pos(x), y_pos(y), sc.camera->fov);
	vector = create_vector(*screen_point, *sc.camera->o);
	i = 0;
	while (sc.objects->spheres[i] != NULL)
	{
		colors = rgb(sc.objects->spheres[i]->color);
		t = vector_x_sphere(*sc.objects->spheres[i], *vector);
		if (t)
		{
			double alpha = get_brightness_level(sc.objects->spheres[i], sc.lights, create_point(0 + t * (screen_point->x - 0),  0 + t * (screen_point->y - 0), 0 + t * (screen_point->z - 0)));
			if (alpha > 255)
				printf("%d\n", alpha);
			int rgb[] = {(int)alpha, (int)alpha , (int)alpha };
			color = hexa(rgb);
			//if (color != 0)
			//	printf("%d\n", rgb[0]);
		}
		i++;
	}
	my_mlx_pixel_put(data, x, y, color);
}


int main()
{
	void		*mlx;
	void		*mlx_win;
	t_data		img;
	t_scene		*scene;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIN_HEIGHT, WIN_WIDTH, "HOLA");
	img.img = mlx_new_image(mlx, WIN_HEIGHT, WIN_WIDTH);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	scene = initialize_scene();
	render_screen(&img, scene);
	print_light(&img, scene);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
