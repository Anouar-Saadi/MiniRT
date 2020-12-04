/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 17:30:43 by asaadi            #+#    #+#             */
/*   Updated: 2020/11/18 11:01:39 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void ft_free_split(char **split)
{
    int i;

    i = 0;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}

void ft_add_lights(t_light **alst, t_light *new)
{
    if (!*alst)
    {
        *alst = new;
    }
    else if (alst && new)
    {
        new->next = *alst;
        *alst = new;
    }
}

void ft_add_objects(t_objects **alst, t_objects *new)
{

    if (!*alst)
    {
        *alst = new;
    }
    else if (alst && new)
    {
        new->next = *alst;
        *alst = new;
    }
}

void ft_add_cameras(t_camera **alst, t_camera *new)
{
    if (!*alst)
    {
        *alst = new;
    }
    else if (alst && new)
    {
        new->next = *alst;
        *alst = new;
    }
}

void parser_resolution(t_mlx *mlx, char *line)
{
    char **split;

    split = ft_split(line, ' ');
    mlx->x_res = ft_strtod(split[1]);
    mlx->y_res = ft_strtod(split[2]);
    ft_free_split(split);
}

void parser_ambiant_light(t_data *data, char *line)
{
    char **split;
    char **split2;

    split = ft_split(line, ' ');
    data->illum.ka = ft_strtod(split[1]);
    split2 = ft_split(split[2], ',');
    data->illum.amb_col.r = ft_strtod(split2[0]);
    data->illum.amb_col.g = ft_strtod(split2[1]);
    data->illum.amb_col.b = ft_strtod(split2[2]);
    ft_free_split(split2);
    ft_free_split(split);
}

void parser_light(t_data *data, char *line)
{
    t_light *light;
    char **split;
    char **split2;

    light = malloc(sizeof(t_light));
    split = ft_split(line, ' ');
    light->kd = ft_strtod(split[2]);
    split2 = ft_split(split[1], ',');
    light->position.x = ft_strtod(split2[0]);
    light->position.y = ft_strtod(split2[1]);
    light->position.z = ft_strtod(split2[2]);
    ft_free_split(split2);
    split2 = ft_split(split[3], ',');
    light->intensity.r = ft_strtod(split2[0]);
    light->intensity.g = ft_strtod(split2[1]);
    light->intensity.b = ft_strtod(split2[2]);
    ft_free_split(split2);
    ft_free_split(split);
    light->next = NULL;
    ft_add_lights(&data->light, light);
}

void parser_camera(t_data *data, char *line)
{
    t_camera *camera;
    char **split;
    char **split2;

    camera = malloc(sizeof(t_camera));
    split = ft_split(line, ' ');
    split2 = ft_split(split[1], ',');
    camera->eye.x = ft_strtod(split2[0]);
    camera->eye.y = ft_strtod(split2[1]);
    camera->eye.z = ft_strtod(split2[2]);
    ft_free_split(split2);
    split2 = ft_split(split[2], ',');
    camera->look_at.x = ft_strtod(split2[0]);
    camera->look_at.y = ft_strtod(split2[1]);
    camera->look_at.z = ft_strtod(split2[2]);
    ft_free_split(split2);
    camera->fov = ft_strtod(split[3]);
    ft_free_split(split);
    camera->next = NULL;
    ft_add_cameras(&data->camera, camera);
}

void parser_sphere(t_data *data, char *line)
{
    char **split;
    char **split2;
    t_objects *obj;

    obj = malloc(sizeof(t_objects));
    obj->obj_type = SP;
    split = ft_split(line, ' ');
    split2 = ft_split(split[1], ',');
    obj->sphere.center.x = ft_strtod(split2[0]);
    obj->sphere.center.y = ft_strtod(split2[1]);
    obj->sphere.center.z = ft_strtod(split2[2]);
    ft_free_split(split2);
    obj->sphere.radius = ft_strtod(split[2]);
    split2 = ft_split(split[3], ',');
    obj->sphere.s_color.r = ft_strtod(split2[0]);
    obj->sphere.s_color.g = ft_strtod(split2[1]);
    obj->sphere.s_color.b = ft_strtod(split2[2]);
    ft_free_split(split2);
    ft_free_split(split);
    obj->next = NULL;
    // (*index_obj) += 1;
    ft_add_objects(&data->objects, obj);
}

void parser_plane(t_data *data, char *line)
{
    char **split;
    char **split2;
    t_objects *obj;

    obj = malloc(sizeof(t_objects));
    obj->obj_type = PL;
    split = ft_split(line, ' ');
    split2 = ft_split(split[1], ',');
    obj->plane.point_at_pl.x = ft_strtod(split2[0]);
    obj->plane.point_at_pl.y = ft_strtod(split2[1]);
    obj->plane.point_at_pl.z = ft_strtod(split2[2]);
    ft_free_split(split2);
    split2 = ft_split(split[2], ',');
    obj->plane.plane_norm.x = ft_strtod(split2[0]);
    obj->plane.plane_norm.y = ft_strtod(split2[1]);
    obj->plane.plane_norm.z = ft_strtod(split2[2]);
    ft_free_split(split2);
    split2 = ft_split(split[3], ',');
    obj->plane.pl_col.r = ft_strtod(split2[0]);
    obj->plane.pl_col.g = ft_strtod(split2[1]);
    obj->plane.pl_col.b = ft_strtod(split2[2]);
    ft_free_split(split2);
    ft_free_split(split);
    obj->next = NULL;
    ft_add_objects(&data->objects, obj);
}

void parser_square(t_data *data, char *line)
{
    char **split;
    char **split2;
    t_objects *obj;

    obj = malloc(sizeof(t_objects));
    obj->obj_type = SQ;
    split = ft_split(line, ' ');
    split2 = ft_split(split[1], ',');
    obj->square.sq_center.x = ft_strtod(split2[0]);
    obj->square.sq_center.y = ft_strtod(split2[1]);
    obj->square.sq_center.z = ft_strtod(split2[2]);
    ft_free_split(split2);
    split2 = ft_split(split[2], ',');
    obj->square.or_vec.x = ft_strtod(split2[0]);
    obj->square.or_vec.y = ft_strtod(split2[1]);
    obj->square.or_vec.z = ft_strtod(split2[2]);
    ft_free_split(split2);
    obj->square.size_side = ft_strtod(split[3]);
    split2 = ft_split(split[4], ',');
    obj->square.sq_col.r = ft_strtod(split2[0]);
    obj->square.sq_col.g = ft_strtod(split2[1]);
    obj->square.sq_col.b = ft_strtod(split2[2]);
    ft_free_split(split2);
    ft_free_split(split);
    obj->next = NULL;
    ft_add_objects(&data->objects, obj);
}

void parser_cylinder(t_data *data, char *line)
{
    char **split;
    char **split2;
    t_objects *obj;

    obj = malloc(sizeof(t_objects));
    obj->obj_type = CY;
    split = ft_split(line, ' ');
    split2 = ft_split(split[1], ',');
    obj->cylinder.pos.x = ft_strtod(split2[0]);
    obj->cylinder.pos.y = ft_strtod(split2[1]);
    obj->cylinder.pos.z = ft_strtod(split2[2]);
    ft_free_split(split2);
    split2 = ft_split(split[2], ',');
    obj->cylinder.normal.x = ft_strtod(split2[0]);
    obj->cylinder.normal.y = ft_strtod(split2[1]);
    obj->cylinder.normal.z = ft_strtod(split2[2]);
    ft_free_split(split2);
    obj->cylinder.diameter = ft_strtod(split[3]);
    obj->cylinder.height = ft_strtod(split[4]);
    split2 = ft_split(split[5], ',');
    obj->cylinder.col.r = ft_strtod(split2[0]);
    obj->cylinder.col.g = ft_strtod(split2[1]);
    obj->cylinder.col.b = ft_strtod(split2[2]);
    ft_free_split(split2);
    ft_free_split(split);
    obj->next = NULL;
    ft_add_objects(&data->objects, obj);
}

void parser_triangle(t_data *data, char *line)
{
    char **split;
    char **split2;
    t_objects *obj;

    obj = malloc(sizeof(t_objects));
    obj->obj_type = TR;
    split = ft_split(line, ' ');
    split2 = ft_split(split[1], ',');
    obj->triangle.first_point.x = ft_strtod(split2[0]);
    obj->triangle.first_point.y = ft_strtod(split2[1]);
    obj->triangle.first_point.z = ft_strtod(split2[2]);
    ft_free_split(split2);
    split2 = ft_split(split[2], ',');
    obj->triangle.second_point.x = ft_strtod(split2[0]);
    obj->triangle.second_point.y = ft_strtod(split2[1]);
    obj->triangle.second_point.z = ft_strtod(split2[2]);
    ft_free_split(split2);
    split2 = ft_split(split[3], ',');
    obj->triangle.third_point.x = ft_strtod(split2[0]);
    obj->triangle.third_point.y = ft_strtod(split2[1]);
    obj->triangle.third_point.z = ft_strtod(split2[2]);
    ft_free_split(split2);
    split2 = ft_split(split[4], ',');
    obj->triangle.tr_col.r = ft_strtod(split2[0]);
    obj->triangle.tr_col.g = ft_strtod(split2[1]);
    obj->triangle.tr_col.b = ft_strtod(split2[2]);
    ft_free_split(split2);
    ft_free_split(split);
    obj->next = NULL;
    ft_add_objects(&data->objects, obj);
}