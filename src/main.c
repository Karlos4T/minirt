/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:34:01 by carlosga          #+#    #+#             */
/*   Updated: 2024/02/01 16:54:27 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../minirt.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

int hexa(int *rgb)
{
	int hexa;
	
	hexa = (rgb[0] << 16) + (rgb[1] << 8) + rgb[2];
	return (hexa);
}

void print_square(t_data *data)
{
    int x;
    int y;

    y = 0;
    while(y < WIN_HEIGHT)
    {
        x = 0;
        while(x < WIN_WIDTH)
        {
            if (x == WIN_HEIGHT / 2 || y == WIN_WIDTH / 2)
                my_mlx_pixel_put(data, x, y, 0x00FF0000);
            x++;
        }
        y++;
    }
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

double intensity(int x, int y, t_light *light)
{
	return(1 - vector_module(x, y, light->x_origin, light->y_origin) / light->radius);
}

t_sphere *create_sphere(int x, int y, int radius, int color)
{
    t_sphere *sphere;

    sphere = malloc(sizeof(t_sphere));
    sphere->x_origin = x;
    sphere->y_origin = y;
    sphere->radius = radius;
    sphere->color = rgb(color);

    return sphere;
}

int pixl_color(t_sphere *sphere, t_light *light, int x, int y)
{
    int *color;
	
	(void)x;
	(void)y;
	color = malloc(sizeof(int) * 3);
	printf("%f", intensity(x, y, light));
	color[0] = sphere->color[0] * intensity(x, y, light);
	color[1] = sphere->color[1] * intensity(x, y, light);
	color[2] = sphere->color[2] * intensity(x, y, light);
	//color[0] = (sphere->color[0] < 0) ? 0 : (light->color[0] > 255) ? 255 : light->color[0];
	//color[1] = (sphere->color[1] < 1) ? 1 : (light->color[1] > 255) ? 255 : light->color[1];
	//color[2] = (sphere->color[2] < 2) ? 2 : (light->color[2] > 255) ? 255 : light->color[2];

    return (hexa(color));
}

t_light *create_light(int x, int y, int radius, int color)
{
    t_light *light;

    light = malloc(sizeof(t_light));
    light->x_origin = x;
    light->y_origin = y;
    light->radius = radius;
    light->color = rgb(color);
    return (light);
}

void print_circle(t_data *data, t_sphere *sphere, t_light *light)
{
    int         x;
    int         y;

    y = 0;
    while(y < WIN_HEIGHT)
    {
        x = 0;
        while(x < WIN_WIDTH)
        {
            if(vector_module(x, y, sphere->x_origin, sphere->y_origin) < sphere->radius)              
            my_mlx_pixel_put(data, x, y, pixl_color(sphere, light, x, y));
            if (x_pos(x) == sphere->x_origin)
                my_mlx_pixel_put(data, x, y, 0x0000FF00);
            if (y_pos(y) == sphere->y_origin)
                my_mlx_pixel_put(data, x, y, 0x0000FF00);
            x++;
        }
        y++;
    }
}

int main(int argc, char const *argv[])
{
	void		*mlx;
	void		*mlx_win;
	t_data		img;
	t_sphere	*sphere1, *sphere2;
	t_light		*light;
		
	rgb(0xFF00FF);

	light = create_light(0, 0, 200, 0xFFFFFF);
	sphere1 = create_sphere(100, 100, 150, 0xFFFFFF);
	sphere2 = create_sphere(-200, 100, 100, 0x000000);
	(void)argv;
	(void)argc;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIN_HEIGHT, WIN_WIDTH, "HOLA");
	img.img = mlx_new_image(mlx, WIN_HEIGHT, WIN_WIDTH);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	//print_square(&img);
	print_circle(&img, sphere1, light);
	print_circle(&img, sphere2, light);
	print_square(&img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
