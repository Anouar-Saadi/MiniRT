/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_triangles.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:45:44 by asaadi            #+#    #+#             */
/*   Updated: 2020/11/19 13:02:00 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double inside_outside_test(t_objects *obj, t_coord point)
{
	t_coord vec_per_pl;
	t_coord edge[3];
	t_coord vp[3];
	double n_dot_c;

	edge[0] = sub_vec(&obj->triangle.second_point, &obj->triangle.first_point);
	edge[1] = sub_vec(&obj->triangle.third_point, &obj->triangle.second_point);
	edge[2] = sub_vec(&obj->triangle.first_point, &obj->triangle.third_point);
	vp[0] = sub_vec(&point, &obj->triangle.first_point);
	vp[1] = sub_vec(&point, &obj->triangle.second_point);
	vp[2] = sub_vec(&point, &obj->triangle.third_point);
	vec_per_pl = vec_cross(&edge[0], &vp[0]);
	n_dot_c = vec_dot(obj->triangle.norm_tr, vec_per_pl);
	if (n_dot_c < 0)
		return (0);
	vec_per_pl = vec_cross(&edge[1], &vp[1]);
	n_dot_c = vec_dot(obj->triangle.norm_tr, vec_per_pl);
	if (n_dot_c < 0)
		return (0);
	vec_per_pl = vec_cross(&edge[2], &vp[2]);
	n_dot_c = vec_dot(obj->triangle.norm_tr, vec_per_pl);
	if (n_dot_c < 0)
		return (0);
	return (1.0);
}

double inters_ray_triangle(t_data *data, t_objects *obj, t_ray *ray)
{
	t_coord v[2];
	double dist_o_tr;
	double n_dot_d;
	double n_dot_o;
	t_coord point;

	v[0] = sub_vec(&obj->triangle.second_point, &obj->triangle.first_point);
	v[1] = sub_vec(&obj->triangle.third_point, &obj->triangle.first_point);
	obj->triangle.norm_tr = vec_cross(&v[0], &v[1]);
	obj->triangle.norm_tr = unit_vector(obj->triangle.norm_tr);
	n_dot_d = vec_dot(obj->triangle.norm_tr, ray->direction);
	if (fabs(n_dot_d) > 0)
	{
		dist_o_tr = vec_dot(obj->triangle.norm_tr, obj->triangle.first_point);
		n_dot_o = vec_dot(obj->triangle.norm_tr, ray->origin);
		data->rec.t = ((n_dot_o + dist_o_tr) / n_dot_d);
		if (data->rec.t < 0.0)
			return (0);
		point = point_of_hit(data->rec.t, *ray);
		return (inside_outside_test(obj, point));
	}
	return (0);
}