/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:44:53 by carlosga          #+#    #+#             */
/*   Updated: 2024/04/05 17:30:45 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

int x_pos(int x)
{
    return (x + WIN_WIDTH / 2 - WIN_WIDTH);
}

int y_pos(int y)
{
    return (-y - WIN_HEIGHT / 2 + WIN_HEIGHT);
}

double module(t_vec v)
{
	return(sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec get_point(t_ray r, int t)
{
	t_vec v;
	
	v.x = r.o.x + r.v.x * t;
	v.y = r.o.y + r.v.y * t;
	v.z = r.o.z + r.v.z * t;
	return v;
}

t_vec producto_escalar(t_vec v, double n)
{
	v.x = v.x * n;
	v.y = v.y * n;
	v.z = v.z * n;
	return (v);
}

t_vec normalize(t_vec v)
{
	double m = module(v);
	if (m == 0)
		m = 0.1;

	v.x = v.x / m;
	v.y = v.y / m;
	v.z = v.z / m;
	return(v);
}

t_vec neg(t_vec v)
{
	v.x = -v.x;
	v.y = -v.y;
	v.z = -v.z;
	return (v);
}

t_vec	cross_prod(t_vec u, t_vec v)
{
	t_vec	dst;

	dst.x = u.y * v.z - u.z * v.y;
	dst.y = u.z * v.x - u.x * v.z;
	dst.z = u.x * v.y - u.y * v.x;
	return (dst);
}

t_vec	vec_add(t_vec v1, t_vec v2)
{
	v1.x = v1.x + v2.x;
	v1.y = v1.y + v2.y;
	v1.z = v1.z + v2.z;
	return(v1);
}

t_vec	vec_sub(t_vec v1, t_vec v2)
{
	t_vec	v;
	
	v.x = v2.x - v1.x;
	v.y = v2.y - v1.y;
	v.z = v2.z - v1.z;
	return (v);
}

double dot_prod(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double quadratic(double a, double b, double c)
{
	double D;
	double t[2];

	D = b * b - (4 * a * c);
	if (D >= 0)
	{
		t[0] = (- b + sqrt(D)) / (2 * a);
		t[1] = (- b - sqrt(D)) / (2 * a);
		if (fabs(t[0]) < fabs(t[1]))
			return (fabs(t[0]));
		return (fabs(t[1]));
	}
	return (0);
}

/*
t_vec *get_screen_coord(int x, int y, t_camera *c)
{
    t_vec *coords;
    t_vec right, up, forward;
    double aspect_ratio = (double)WIN_WIDTH / WIN_HEIGHT;
    double wsize;

    coords = malloc(sizeof(t_vec));

    // Calcula el tamaño de la ventana en términos de la proyección
    wsize = tan(c->fov / 2);

    // Normaliza la dirección de la cámara
    forward = normalize(c->v);

    // Calcula el vector hacia arriba (up) de la cámara
    t_vec global_up = {0, 0, 1}; // Suponiendo que Y es el eje hacia arriba en el mundo
    right = normalize(cross_prod(global_up, forward));
    up = cross_prod(forward, right);

    // Coordenadas de la pantalla al espacio
    double pixel_ndc_x = (x + 0.5) / WIN_WIDTH; // Coordenadas normalizadas de dispositivo
    double pixel_ndc_y = (y + 0.5) / WIN_HEIGHT;
    double pixel_screen_x = (2 * pixel_ndc_x - 1) * aspect_ratio * wsize;
    double pixel_screen_y = (1 - 2 * pixel_ndc_y) * wsize;

    // Calcula las coordenadas del espacio
    coords->x = c->o.x + pixel_screen_x * right.x + pixel_screen_y * up.x - forward.x;
    coords->y = c->o.y + pixel_screen_x * right.y + pixel_screen_y * up.y - forward.y;
    coords->z = c->o.z + pixel_screen_x * right.z + pixel_screen_y * up.z - forward.z;

    return coords;
}
*/

void rotate_vector(t_vec *vec, float rotation_matrix[3][3])
{
    float x = vec->x;
    float y = vec->y;
    float z = vec->z;

    vec->x = rotation_matrix[0][0] * x + rotation_matrix[0][1] * y + rotation_matrix[0][2] * z;
    vec->y = rotation_matrix[1][0] * x + rotation_matrix[1][1] * y + rotation_matrix[1][2] * z;
    vec->z = rotation_matrix[2][0] * x + rotation_matrix[2][1] * y + rotation_matrix[2][2] * z;
}

// Calcular la matriz de rotación
void calculate_rotation_matrix_y(float rotation_matrix[3][3], double angle_y)
{
    float sin_y = sinf(angle_y);
    float cos_y = cosf(angle_y);

    rotation_matrix[0][0] = cos_y;
    rotation_matrix[0][1] = 0;
    rotation_matrix[0][2] = sin_y;
    rotation_matrix[1][0] = 0;
    rotation_matrix[1][1] = 1;
    rotation_matrix[1][2] = 0;
    rotation_matrix[2][0] = -sin_y;
    rotation_matrix[2][1] = 0;
    rotation_matrix[2][2] = cos_y;
}

void calculate_rotation_matrix_x(float rotation_matrix[3][3], double angle_x)
{
    float sin_x = sinf(angle_x);
    float cos_x = cosf(angle_x);

    rotation_matrix[0][0] = 1;
    rotation_matrix[0][1] = 0;
    rotation_matrix[0][2] = 0;
    rotation_matrix[1][0] = 0;
    rotation_matrix[1][1] = cos_x;
    rotation_matrix[1][2] = -sin_x;
    rotation_matrix[2][0] = 0;
    rotation_matrix[2][1] = sin_x;
    rotation_matrix[2][2] = cos_x;
}

void combine_rotation_matrices(float combined[3][3], float ry[3][3], float rx[3][3])
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            combined[i][j] = ry[i][0] * rx[0][j] + ry[i][1] * rx[1][j] + ry[i][2] * rx[2][j];
        }
    }
}

void rotate_camera(t_camera *camera, double angle_y, double angle_x)
{
    float rotation_matrix_y[3][3];
    float rotation_matrix_x[3][3];
    float rotation_matrix_combined[3][3];

    calculate_rotation_matrix_y(rotation_matrix_y, angle_y);
    calculate_rotation_matrix_x(rotation_matrix_x, angle_x);
    combine_rotation_matrices(rotation_matrix_combined, rotation_matrix_y, rotation_matrix_x);

    // Actualizar la matriz de rotación de la cámara
    memcpy(camera->rotation_matrix, rotation_matrix_combined, sizeof(rotation_matrix_combined));
}

t_vec *get_screen_coord(int x, int y, t_camera *c)
{
    t_vec *coords;
    double wsize;

    coords = malloc(sizeof(t_vec));
    if (!coords)
        return NULL; // Manejar error de memoria

    wsize = fabs(tan(c->fov / 2));

    // Coordenadas en el plano de la cámara antes de la rotación
    coords->x = (x - WIN_WIDTH / 2.0) * wsize / (WIN_HEIGHT / 2.0);
    coords->y = (y - WIN_HEIGHT / 2.0) * wsize / (WIN_HEIGHT / 2.0);
    coords->z = -1; // Considerando el plano de la cámara en z = -1

    // Aplicar la rotación combinada
    rotate_vector(coords, c->rotation_matrix);

    // Transformar a las coordenadas globales (espacio 3D)
    coords->x += c->o.x;
    coords->y += c->o.y;
    coords->z += c->o.z;

    return coords;
}


