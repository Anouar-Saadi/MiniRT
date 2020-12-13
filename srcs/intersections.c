/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:56:29 by asaadi            #+#    #+#             */
/*   Updated: 2020/12/07 08:32:59 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_coord	normal_at_cylinder(t_data *data, t_objects *obj)
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

t_coord			normal_at_triangle(t_data *data, t_objects *obj)
{
	t_coord edge[2];
	t_coord normal;

	edge[0] = sub_vec(&obj->triangle.second_point, &obj->triangle.first_point);
	edge[1] = sub_vec(&obj->triangle.third_point, &obj->triangle.first_point);
	normal = vec_cross(&edge[0], &edge[1]);
	if (vec_dot(data->ray.direction, normal) > 0)
		normal = vect_scal(-1, normal);
	normal = unit_vector(normal);
	return (normal);
}

void			calcul_normal_at_hit_point(t_data *data, t_objects *obj)
{
	if (obj->obj_type == SP)
		data->rec.normal = sub_vec(&data->rec.hit_point, &obj->sphere.center);
	else if (obj->obj_type == PL)
		data->rec.normal = obj->plane.plane_norm;
	else if (obj->obj_type == TR)
		data->rec.normal = normal_at_triangle(data, obj);
	else if (obj->obj_type == SQ)
		data->rec.normal = obj->square.or_vec;
	else if (obj->obj_type == CY)
		data->rec.normal = normal_at_cylinder(data, obj);
	data->rec.normal = unit_vector(data->rec.normal);
}

int				intersection_ray_obj(t_data *data,
		t_objects *tmp_objs, t_ray *ray)
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

t_objects		*find_the_closest_obj(t_data *data, t_ray *ray, t_objects *obj)
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
				if (!closest_obj && data->rec.t >= 0)
				{
					data->rec.t_closest = data->rec.t;
					closest_obj = tmp_objs;
				}
				else if (data->rec.t < data->rec.t_closest && data->rec.t >= 0)
				{
					data->rec.t_closest = data->rec.t;
					closest_obj = tmp_objs;
				}
			}
		tmp_objs = tmp_objs->next;
	}
	return (closest_obj);
}
