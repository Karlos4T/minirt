
#ifndef MINIRT
# define MINIRT

#define WIN_WIDTH 1440
#define WIN_HEIGHT 1080

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
	int radius;
	int	*color;
} t_sphere;

typedef struct s_cylinder {
	t_cords		o;
	t_vector	v;
	double		radius;
	double		height;
	int	*color;
} t_cylinder;

typedef struct s_plane {
	t_cords		o;
	t_vector	v;
	int			*color;
} t_plane;

typedef struct s_light {
	t_cords	o;
	int	x_origin;
	int	y_origin;
	int z_origin;
	double intensity;
	int	*color;
} t_light;

typedef struct s_alight {
	double intensity;
	int	*color;
} t_alight;

typedef struct s_objects {
	t_cylinder	**cylinders;
	t_sphere	**spheres;
	t_plane		**planes;
} t_objects;

typedef struct s_scene {
	t_camera 	*camera;
	t_objects	*objects;
	t_light 	*lights;
	t_alight 	*alight;
} t_scene;

//FUNCTIONS
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_sphere	*create_sphere(int x, int y, int z, int radius, int color);
t_vector	*create_vector(t_cords point1, t_cords point2);
double		vector_x_sphere(t_sphere s, t_vector v);
double		vector_x_plane(t_plane pl, t_vector v);
void		render_screen(t_data *data, t_scene *scene);
t_cords 	*create_point(int x, int y, int z);
t_light		*create_light(int x, int y, int z, double intensity, int color);
t_camera 	*start_camera(int x, int y, int z, int fov);
t_plane		*create_plane(int x, int y, int z, double vx, double vy, double vz, int color);
t_alight	*create_alight(double intensity, int color);
t_cylinder	*create_cylinder(int x, int y, int z, double vx, double vy, double vz, double radius, double height, int color);
double		vector_x_cylinder(t_cylinder cy, t_vector v);

//MATH FUNCTIONS
int			x_pos(int x);
int			y_pos(int y);
int			hexa(int *rgb);
int			*rgb(int color);
double		module(t_vector v);
t_vector	unit_vector(t_vector v);

//COLOR
int 	*multiply_colors(int *rgb1, int *rgb2, double alpha, double al);
double 	get_brightness_level(t_sphere *s, t_light *l, t_cords *p);
double 	get_brightness_level_plane(t_plane *s, t_light *l, t_cords *p);


//MAIN
void render_pixel(int x, int y, t_data *data, t_scene scene);
t_cords	*get_screen_coord(int x, int y, int fov);
t_scene *initialize_scene();




#endif