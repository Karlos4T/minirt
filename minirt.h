
#ifndef MINIRT
# define MINIRT

#define WIN_WIDTH 1024
#define WIN_HEIGHT 1024

# include <mlx.h>
# include <math.h>
# include <stdlib.h>

typedef struct s_cords {
	double	x;
	double	y;
	double	z;
}	t_cords;

typedef struct s_vector {
	double x;
	double	y;
	double z;
	
} t_vector;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_data;

typedef struct	s_camera {
	t_cords	*cords;
	int dir;
	int fov;
}	t_camera;

typedef struct s_sphere {
	int	x;
	int	y;
	int z;
	int radius;
	int	*color;
} t_sphere;

typedef struct s_light {
	int	x_origin;
	int	y_origin;
	int z_origin;
	int radius;
	int	*color;
} t_light;



//MATH FUNCTIONS
int		x_pos(int x);
int		y_pos(int y);
int		vector_module(int x, int y, int x_origin, int y_origin);



#endif