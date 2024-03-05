/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosga <carlosga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:18:32 by carlosga          #+#    #+#             */
/*   Updated: 2024/03/05 13:46:13 by carlosga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_cylinder	*create_cylinder(int x, int y, int z, double vx, double vy, double vz, double radius, double height, int color)
{
	t_cylinder	*cy;

	cy = malloc(sizeof(t_plane));
	cy->o.x = x;
	cy->o.y = y;
	cy->o.z = z;
	cy->v.x = vx;
	cy->v.y = vy;
	cy->v.z = vz;
    cy->radius = radius;
    cy->height = height;
	cy->color = rgb(color);
	return (cy);
}

double	vector_x_cylinder(t_cylinder cy, t_vector v)
{
	double	t[2];
	double	a;
	double	b;
	double	c;
	double	D;
	//cdouble v1[2];
	//cdouble co[2];
	//dependiendo de la direccion que introduzca se cogera un valor u otro para operar
	/*if(cy.v.y == 1)
	{
		v1[0] = v.x;
		v1[1] = v.z;
		co[0] = cy.o.x;
		co[1] = cy.o.z;
	}
	else if(cy.v.x == 1)
	{
		v1[0] = v.y;
		v1[1] = v.z;
		co[0] = cy.o.y;
		co[1] = cy.o.z;
	}
	else if(cy.v.z == 1)
	{
		v1[0] = v.y;
		v1[1] = v.x;
		co[0] = cy.o.y;
		co[1] = cy.o.x;
	}*/
	//v = unit_vector(v); //esta linea curva el cilindro en funcion de x. Curioso
	
	//TODOS LOS 0 SE DEBEN SUSTITUIR POR LAS CORDENADAS DEL ORIGEN DEL VECTOR, ES DECIR, LA CAMARA
	
	a = pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2) \
		 - (pow(cy.v.x, 2) * pow(v.x, 2) + pow(cy.v.y, 2) * pow(v.y, 2) + pow(cy.v.z, 2) * pow(v.z, 2));
	b = 2 * (v.x * (0 - cy.o.x) + v.y * (0 - cy.o.y) + v.z * (0 - cy.o.z)) \
		;//- 2 * ((cy.v.x * 0 + cy.v.y * 0 + cy.v.z * 0) - (cy.o.x * cy.v.x * v.x + cy.o.y * cy.v.y * v.y + cy.o.z * cy.v.z * v.z));
	
	
	//2 * v.x * (/*(origen vector) xo*/ 1 - cy.o.x) + 2 * v.y * (/*(origen vector) yo*/ 1 - cy.o.y) + 2 * v.z * (/*(origen vector) yo*/ 1 - cy.o.z)
		//- (2 * (-(cy.o.x * cy.v.x * v.x + cy.o.y * cy.v.y * v.y + cy.o.z * cy.v.z * v.z) + (/*(origen vector) xo*/0 * cy.v.x + /*(origen vector) xo*/0 * cy.v.y + /*(origen vector) xo*/0 * cy.v.z)) );
	c = pow(0 - cy.o.x, 2) + pow(0 - cy.o.y, 2) + (pow(0 - cy.o.z, 2)) - pow(cy.radius, 2) \
		;// - (pow(cy.o.x, 2) + pow(cy.o.y, 2) + pow(cy.o.z, 2) + 2 * (cy.o.x * cy.o.y + cy.o.x * cy.o.z + cy.o.y * cy.o.z) - (pow(cy.v.x, 2) * pow(0, 2) * pow(cy.v.y, 2) * pow(0, 2) * pow(cy.v.z, 2) * pow(0, 2)));
	//-2 * (cy.o.x * cy.o.y + cy.o.x * cy.o.z + cy.o.y * cy.o.z) - pow(cy.radius, 2);
	
	
	if (cy.height / 2 + cy.o.y)
		D = b * b - (4 * a * c);
	else
		D = -1;
	//printf("v (x:%f y:%f z:%f)", v.x, v.y, v.z);
	//printf("cy(x:%f y:%f z:%f) ", cy.o.x, cy.o.y, cy.o.z);
	//printf("a:%f b:%f c:%f D: %f ", a, b, c, D);
	if (D >= 0)
	{
		t[0] = (- b + sqrt(D)) / (2 * a);
		t[1] = (- b - sqrt(D)) / (2 * a);
	//	printf("t1:%f t2:%f ", t[0], t[1]);
	//	printf("\n");
		printf("\n");
		if (t[0] > t[1])
			return (t[0]);
		return (t[1]);
	}
	return (0);
}

double plane_x_cylinder(t_cylinder cy, t_vector v)
{
	int		t;
	t_plane	*pl;

	pl = create_plane(cy.o.x + cy.height / 2 * cy.v.x,  cy.o.y + cy.height / 2 * cy.v.y, cy.o.z + cy.height / 2 * cy.v.z, cy.v.x, cy.v.y, cy.v.z, hexa(cy.color));
	t = - (pl->o.x * cy.o.x + pl->o.y * cy.o.y + pl->o.z * cy.o.z + cy.height/2) / (pl->o.x * v.x + pl->o.y * v.y + pl->o.z * v.z);
	return (t);
}

double	get_brightness_level_cylinder(t_cylinder *c, t_light *l, t_cords *p)
{
	//t_vector	*v1;
	t_vector	*v2;
	t_vector	*v3;
	double		alpha;

	//v1 = create_vector(c->o, *p);
	v2 = create_vector(l->o, *p);
	v3 = create_vector(l->o, c->o);
	alpha = module(*v2) - module(*v3) + c->radius;
	alpha = (1 - (alpha / c->radius)) * l->intensity;
	//free(v1);
	free(v2);
	free(v3);
	return (alpha);
}
