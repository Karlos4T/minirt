/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:34:01 by carlosga          #+#    #+#             */
/*   Updated: 2024/02/14 18:08:06 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../minirt.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

int *rgb(int color)
{
	int *rgb;

	rgb = malloc(sizeof(int) * 3);
	rgb[0] = (color) >> 16;
	rgb[1] = (color) >> 8;
	rgb[2] = (color);

	return (rgb);
}

t_sphere *create_sphere(int x, int y, int z, int radius, int color)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	sphere->x = x;
	sphere->y = y;
	sphere->z = z;
	sphere->radius = radius;
	sphere->color = rgb(color);

	return sphere;
}

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

int check_parallelism(t_vector vec1, t_vector vec2)
{
	if (vec1.x * vec2.y - vec2.x * vec1.y != 0)
		return (0);
	if (vec1.x * vec2.z - vec2.x * vec1.z != 0)
		return (0);
	if (vec1.y * vec2.z - vec2.y * vec1.z != 0)
		return (0);
	return (1);
}

t_vector *create_vector(t_cords point1, t_cords point2)
{
	t_vector *vector;

	vector = malloc(sizeof(t_vector));
	vector->x = point1.x + point2.x;
	vector->y = point1.y + point2.y;
	vector->z = point1.z + point2.z;
	return (vector);
}

void shot_ray(t_vector *vec1, t_vector *vec2)
{
	vec1->x = 0;
	vec1->y	= 0;
	vec1->z	= -1;

	vec2->x = 0;
	vec2->y	= 0;
	vec2->z	= -100;
	printf("%d\n", check_parallelism(*vec1, *vec2));
}

t_cords *get_screen_coord(int x, int y, int fov)
{
	t_cords	*coords;
	double	limit;
	
	limit = tan(fov/2);	
	coords = malloc(sizeof(t_cords));
	coords->x = x * limit / WIN_WIDTH;
	coords->y = y * limit / WIN_HEIGHT;
	coords->z = -1;
	return(coords);
}

int vector_x_sphere(t_sphere s, t_vector v)
{
	double t[2];
	double a;
	double b;
	double c;
	int	D;
	
	a = pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2);
	b = 2 * (v.x * (s.x - v.x) + v.y * (s.y - v.y) + v.z * (s.z - v.z));
	c = pow(s.x - v.x, 2) + pow(s.y - v.y, 2) + pow(s.z - v.z, 2) - pow(s.radius, 2);
	
	D = b * b - (4 * a * c);

	if (D == 0)
		t[0] = - b / 2 * a;
	else if (D > 0)
	{
		t[0] = (- b + sqrt(D)) / (2 * a);
		t[1] = (- b - sqrt(D)) / (2 * a);
		return (1);
	}
	else
		return (0);
	
	//printf(" %f, %f\n", t[0], t[1]);
	if(v.x == 0 && v.y == 0)
	{
		printf("%f\n", sqrt(pow(b, 2) - 4 * a * c));
		printf("a = %f, b = %f, c = %f\n", a, b, c);	
		printf("for Vo = (%f, %f, %f) and So = (%d, %d, %d) t0 = %f, t1 = %f\n", v.x, v.y, v.z, s.x, s.y, s.z, t[0], t[1]);
	}
	if ((t[0] >= 0 && t[0] <= 1) || (t[1] >= 0 && t[1] <= 1))
	{
		//printf("%f, %f\n", t[0], t[1]);
		return (1);
	}
	return (0);
}

void render_pixel(int x, int y, t_data *data)
{
	t_cords		*screen_point;
	t_cords		*origin;
	t_vector	*vector;
	t_sphere	*sphere;
	int color = 0X000000;
	
	sphere = create_sphere(0, 0, -10, 5, 0xFFFFFF);
	origin = malloc(sizeof(t_cords));
	origin->x = 0;
	origin->y = 0;
	origin->z = 0;
	screen_point = get_screen_coord(x_pos(x), y_pos(y), 90);
	//printf("Sp = (%f, %f, %f) \n", screen_point->x, screen_point->y, screen_point->z);
	
	vector = create_vector(*screen_point, *origin);
	if(vector->x == 0 && vector->y == 0)
	{
		printf("origin vector \n");
		printf("Sp = (%f, %f, %f) \n", screen_point->x, screen_point->y, screen_point->z);
		printf("Vo = (%f, %f, %f) \n", vector->x, vector->y, vector->z);
		
	}
	//printf("Vo = (%f, %f, %f) \n", vector->x, vector->y, vector->z);
	//printf("%d\n", vector_x_sphere(*sphere, *vector));
	if (vector_x_sphere(*sphere, *vector))
		color = 0XFFFFFF;
	my_mlx_pixel_put(data, x, y, color);
}

void render_screen(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			render_pixel(i, j, data);
			j++;
		}
		i++;
	}
}


int main()
{
	void		*mlx;
	void		*mlx_win;
	t_data		img;
	t_camera	*camera;

	camera = start_camera(0, 0, 0, 70);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIN_HEIGHT, WIN_WIDTH, "HOLA");
	img.img = mlx_new_image(mlx, WIN_HEIGHT, WIN_WIDTH);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	render_screen(&img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
