/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:56:29 by asaadi            #+#    #+#             */
/*   Updated: 2020/11/19 19:32:13 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* CYLINDER
        t_coord p_c;
        t_coord n_x_m;
    
        p_c = sub_vec(&data->rec.point_of_hit, &data->objects->cylinder.pos);
        n_x_m = vect_scal(data->rec.m, data->objects->cylinder.normal);
        data->rec.normal = sub_vec(&p_c, &n_x_m);
        if (vec_dot(&data->rec.normal, &data->ray.direction) > 0)
        data->rec.normal = vect_scal(-1, data->rec.normal);
        data->rec.normal = unit_vector(&data->rec.normal);
        data->rec.light_ray = sub_vec(&data->light->position, &data->rec.point_of_hit);
        data->rec.light_ray = unit_vector(&data->rec.light_ray);*/

/* PLANE
        data->rec.light_ray = sub_vec(&data->light->position, &data->rec.point_of_hit);
        data->rec.light_ray = unit_vector(&data->rec.light_ray);
        
        if (vec_dot(&data->ray.direction, &data->rec.normal) < 0.0)
        data->rec.normal = vect_scal(-1, data->objects->plane.plane_norm);*/

/* SQUARE
        data->rec.light_ray = sub_vec(&data->light->position, &data->rec.point_of_hit);
        data->rec.light_ray = unit_vector(&data->rec.light_ray);
        data->rec.normal = data->objects->square.or_vec;
        data->rec.normal = unit_vector(&data->rec.normal);*/

/* TRIANGLE
        data->rec.light_ray = sub_vec(&data->light->position, &data->rec.point_of_hit);
        data->rec.light_ray = unit_vector(&data->rec.light_ray);
        data->rec.normal = data->rec.normal;*/

/* ILLUMINATION
        amb = amb_light(data);
        deff = deffuse_light(data, &data->rec.normal);
        spec = specular_light(data, &data->rec.normal);
        col = col;  (amb.r + deef.r) * spec.r; */

void ft_init_hit_record(t_hit_rec *hit)
{
    hit->t = -1;
    hit->t_closest = -1;
    hit->m = 0;
    hit->hit_point = new_vector(0.0, 0.0, 0.0);
    hit->normal = new_vector(0.0, 0.0, 0.0);
    hit->light_ray = new_vector(0.0, 0.0, 0.0);
    hit->refl = new_vector(0.0, 0.0, 0.0);
    hit->view = new_vector(0.0, 0.0, 0.0);
}

t_color get_col_obj(t_objects *obj)
{
    t_color col_obj;

    col_obj = get_color(0, 0, 0);
    if (obj->obj_type == SP)
        col_obj = obj->sphere.s_color;
    else if (obj->obj_type == PL)
        col_obj = obj->plane.pl_col;
    else if (obj->obj_type == SQ)
        col_obj = obj->square.sq_col;
    else if (obj->obj_type == TR)
        col_obj = obj->triangle.tr_col;
    else if (obj->obj_type == CY)
        col_obj = obj->cylinder.col;
    return (sca_div_col(col_obj, 255.0));
}

static t_coord normal_at_cylinder(t_data *data, t_objects *obj)
{
    t_coord p_c;
    t_coord n_x_m;
    t_coord nor;
    p_c = sub_vec(&data->rec.hit_point, &obj->cylinder.pos);
    n_x_m = vect_scal(data->rec.m, obj->cylinder.normal);
    nor = sub_vec(&p_c, &n_x_m);
    if (vec_dot(nor, data->ray.direction) > 0)
        nor = vect_scal(-1, nor);
    data->rec.normal = unit_vector(data->rec.normal);
    return (nor);
}

void calcul_normal_at_hit_point(t_data *data, t_objects *obj)
{
    if (obj->obj_type == SP)
        data->rec.normal = sub_vec(&data->rec.hit_point, &obj->sphere.center);
    else if (obj->obj_type == PL)
        data->rec.normal = obj->plane.plane_norm;
    else if (obj->obj_type == TR)
        data->rec.normal = obj->triangle.norm_tr;
    else if (obj->obj_type == SQ)
        data->rec.normal = obj->square.or_vec;
    else if (obj->obj_type == CY)
        data->rec.normal = normal_at_cylinder(data, obj);
    data->rec.normal = unit_vector(data->rec.normal);
}

int intersection_ray_obj(t_data *data, t_objects *tmp_objs, t_ray *ray)
{
    double t_hit;

    t_hit = 0;
    if (tmp_objs->obj_type == SP)
        t_hit = inters_ray_sphere(data, tmp_objs, ray);
    else if (tmp_objs->obj_type == PL)
        t_hit = inters_ray_plan(data, tmp_objs, ray);
    else if (tmp_objs->obj_type == SQ)
        t_hit = inters_ray_square(data, tmp_objs, ray);
    else if (tmp_objs->obj_type == TR)
        t_hit = inters_ray_triangle(data, tmp_objs, ray);
    else if (tmp_objs->obj_type == CY)
        t_hit = inters_ray_cylinder(data, tmp_objs, ray);
    return (t_hit);
}

t_objects *find_the_closest_obj(t_data *data, t_ray *ray, t_objects *obj)
{
    t_objects *closest_obj;
    t_objects *tmp_objs;

    tmp_objs = data->objects;
    closest_obj = NULL;
    while (tmp_objs)
    {
        if (tmp_objs != obj)
            if (intersection_ray_obj(data, tmp_objs, ray) == 1)
            {
                if (!closest_obj)
                {
                    data->rec.t_closest = data->rec.t;
                    closest_obj = tmp_objs;
                }
                else if (data->rec.t < data->rec.t_closest)
                {
                    data->rec.t_closest = data->rec.t;
                    closest_obj = tmp_objs;
                }
            }
        tmp_objs = tmp_objs->next;
    }
    return (closest_obj);
}

t_color compte_lighting(t_data *data, t_objects *obj)
{
    t_color hit_col = get_color(0, 0, 0);
    t_light *tmp_lights;
    t_color amb_col;
    t_color deff_col[2];
    t_color spec_col[2];
    int shad_obj;
    t_ray ray_shad;
    t_color obj_col;

    obj_col = get_col_obj(obj);
    deff_col[0] = get_color(0, 0, 0);
    spec_col[0] = get_color(0, 0, 0);
    tmp_lights = data->light;
    shad_obj = 0;
    amb_col = ambient_light(data);
    while (tmp_lights != NULL)
    {
        data->rec.light_ray = sub_vec(&tmp_lights->position, &data->rec.hit_point);
        data->rec.light_ray = unit_vector(data->rec.light_ray);
        ray_shad.origin.x = data->rec.hit_point.x + 0.0001f;
        ray_shad.origin.y = data->rec.hit_point.y + 0.0001f;
        ray_shad.origin.z = data->rec.hit_point.z + 0.0001f;
        ray_shad.direction = data->rec.light_ray;
        if (find_the_closest_obj(data, &ray_shad, obj) == NULL)
        {
            deff_col[1] = deffuse_light(data, tmp_lights);
            deff_col[0] = add_color(deff_col[0], deff_col[1]);
            spec_col[1] = specular_light(data, tmp_lights);
            spec_col[0] = add_color(spec_col[0], spec_col[1]);
        }
        tmp_lights = tmp_lights->next;
    }
    hit_col.r = obj_col.r * (amb_col.r + deff_col[0].r) + spec_col[0].r;
    hit_col.g = obj_col.g * (amb_col.g + deff_col[0].g) + spec_col[0].g;
    hit_col.b = obj_col.b * (amb_col.b + deff_col[0].b) + spec_col[0].b;
    min_max_color(&hit_col);
    return (hit_col);
}

t_color scene_trace(t_data *data)
{
    t_color background_col;
    t_objects *closest_obj;

    background_col = get_color(0, 0, 0);
    closest_obj = NULL;
    if (data->objects)
    {
        ft_init_hit_record(&data->rec);
        closest_obj = find_the_closest_obj(data, &data->ray, NULL);
        if (!closest_obj)
            return (background_col);
        data->rec.hit_point = point_of_hit(data->rec.t_closest, data->ray);
        calcul_normal_at_hit_point(data, closest_obj);
        return (compte_lighting(data, closest_obj));
    }
    return (background_col);
}