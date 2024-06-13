
#include "../minirt.h"

static void	dot_normal_cylind(t_dist *dist, t_vec *dot, t_vec *normal)
{
	float		n;
	t_vec	tmp;

	tmp = sub_vec(dist->cl_cy->coord, *dot);
	normalize_vec(&dist->cl_cy->orien);
	n = -scalar_vec(tmp, dist->cl_cy->orien);
	normal->x = -(dist->cl_cy->orien.x * n
			+ dist->cl_cy->coord.x - dot->x);
	normal->y = -(dist->cl_cy->orien.y * n
			+ dist->cl_cy->coord.y - dot->y);
	normal->z = -(dist->cl_cy->orien.z * n
			+ dist->cl_cy->coord.z - dot->z);
	normalize_vec(normal);
	normalize_vec(dist->dot_light);
}