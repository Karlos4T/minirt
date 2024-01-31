/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:34:01 by carlosga          #+#    #+#             */
/*   Updated: 2024/01/31 17:13:38 by carlosga         ###   ########.fr       */
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

t_sphere *create_sphere(int x, int y, int radius)
{
    t_sphere *sphere;

    sphere = malloc(sizeof(t_sphere));
    sphere->x_origin = x;
    sphere->y_origin = y;
    sphere->radius = radius;
    return sphere;
}


int axys_coord(int x)
{
    x = x + WIN_WIDTH / 2 - WIN_WIDTH;

    //y = y + WIN_HEIGHT / 2;
    return x;
}

void print_circle(t_data *data)
{
    int         x;
    int         y;
    int         color;
    t_sphere    *sphere;

    y = 0;
    sphere = create_sphere(100, 100, 150);
    while(y < WIN_HEIGHT)
    {
        x = 0;
        while(x < WIN_WIDTH)
        {
            color = 255 - sqrt(pow(axys_coord(x), 2) + pow(axys_coord(y), 2));
            if((sqrt(pow(sphere->x_origin - axys_coord(x), 2) + pow(sphere->y_origin - axys_coord(y), 2))) < sphere->radius)              
                my_mlx_pixel_put(data, x, y, 0x00000000 + color);
            if (axys_coord(x) == sphere->x_origin)
                my_mlx_pixel_put(data, x, y, 0x0000FF00);
            if (axys_coord(y) == sphere->y_origin)
                my_mlx_pixel_put(data, x, y, 0x0000FF00);
            if (axys_coord(y) == 100)
                my_mlx_pixel_put(data, x, y, 0x0000FF00);
            x++;
        }
        if (x < 100 && y < 100)
            printf("\n");
        y++;
    }
}

void map_win()
{
    int x;
    int y;

    x = 0;
    y = 0;
    
    
}

int main(int argc, char const *argv[])
{
    void    *mlx;
    void    *mlx_win;
    t_data  img;

    (void)argv;
    (void)argc;
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, WIN_HEIGHT, WIN_WIDTH, "HOLA");
    img.img = mlx_new_image(mlx, WIN_HEIGHT, WIN_WIDTH);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    //print_square(&img);
    print_circle(&img);
    print_square(&img);
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
    return (0);
}
