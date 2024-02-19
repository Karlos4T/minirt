#include "../minirt.h"

t_scene *initialize_scene()
{
    t_scene *scene;

    scene = malloc(sizeof(t_scene));
    scene->camera = start_camera(0, 0, 0, 90);
    scene->lights = create_light(90, 100, 10, 1, 0xFFFFFF);
    scene->objects = malloc(sizeof(t_objects));
    scene->objects->spheres = malloc(sizeof(t_sphere) * 5);
    scene->objects->spheres[0] = create_sphere(-30, -30, -100, 15, 0xFFFFFF);
    scene->objects->spheres[1] = create_sphere(30, 30, -100, 15, 0x00FFFF);
    scene->objects->spheres[2] = create_sphere(-30, 30, -100, 15, 0xFFFFFF);
    scene->objects->spheres[3] = create_sphere(30, -30, -100, 15, 0x00FFFF);
    scene->objects->spheres[4] = NULL;

    return scene;
}