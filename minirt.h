
#ifndef MINIRT
# define MINIRT

#define WIN_WIDTH 1024
#define WIN_HEIGHT 1024

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>

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
	t_cords	*o;
	int dir;
	int fov;
}	t_camera;

typedef struct s_sphere {
	t_cords	o;
	int	x;
	int	y;
	int z;
	int radius;
	int	*color;
} t_sphere;

typedef struct s_light {
	t_cords	o;
	int	x_origin;
	int	y_origin;
	int z_origin;
	double intensity;
	int	*color;
} t_light;

typedef struct s_objects {
	t_sphere	**spheres;
} t_objects;

typedef struct s_scene {
	t_camera 	*camera;
	t_objects	*objects;
	t_light 	*lights;
} t_scene;

//FUNCTIONS
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_sphere	*create_sphere(int x, int y, int z, int radius, int color);
t_vector	*create_vector(t_cords point1, t_cords point2);
double		vector_x_sphere(t_sphere s, t_vector v);
void		render_screen(t_data *data, t_scene *scene);
t_cords 	*create_point(int x, int y, int z);
t_light		*create_light(int x, int y, int z, int radius, int color);
t_camera 	*start_camera(int x, int y, int z, int fov);

//MATH FUNCTIONS
int		x_pos(int x);
int		y_pos(int y);
int		hexa(int *rgb);
int		*rgb(int color);
double 	module(t_vector v);


//MAIN
void render_pixel(int x, int y, t_data *data, t_scene scene);
t_cords	*get_screen_coord(int x, int y, int fov);
t_scene *initialize_scene();


#endif