
#ifndef MINIRT
# define MINIRT

#define WIN_WIDTH 1024
#define WIN_HEIGHT 1024

# include <mlx.h>
# include <math.h>
# include <stdlib.h>

typedef struct s_sphere {
	int	x_origin;
	int	y_origin;
	int z_origin;
	int radius;
	int	color;
} t_sphere;

typedef struct s_light {
	int	x_origin;
	int	y_origin;
	int z_origin;
	int radius;
	int	color;
} t_light;


//MATH FUNCTIONS
int		x_pos(int x);
int		y_pos(int y);
int		vector_module(int x, int y, int x_origin, int y_origin);



#endif