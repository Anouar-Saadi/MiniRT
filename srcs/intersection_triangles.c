/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_triangles.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 10:08:38 by asaadi            #+#    #+#             */
/*   Updated: 2020/12/04 13:49:31 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** pvec = vec[2]
** qvec = vec[3]
** tvec = vec[4]
*/

double			inters_ray_triangle(t_data *data, t_objects *obj, t_ray *ray)
{
	t_coord		vec[5];
	double		det;
	double		invdet;
	double		u;
	double		v;

	vec[0] = sub_vec(&obj->triangle.second_point, &obj->triangle.first_point);
	vec[1] = sub_vec(&obj->triangle.third_point, &obj->triangle.first_point);
	vec[2] = vec_cross(&ray->direction, &vec[1]);
	det = vec_dot(vec[0], vec[2]);
	if (fabs(det) < 0.0000001)
		return (0);
	invdet = 1.0 / det;
	vec[4] = sub_vec(&ray->origin, &obj->triangle.first_point);
	u = vec_dot(vec[4], vec[2]) * invdet;
	if (u < 0.0 || u > 1.0)
		return (0);
	vec[3] = vec_cross(&vec[4], &vec[0]);
	v = vec_dot(ray->direction, vec[3]) * invdet;
	if (v < 0.0 || u + v > 1.0)
		return (0);
	data->rec.t = vec_dot(vec[1], vec[3]) * invdet;
	if (data->rec.t > 0.0000001)
		return (1);
	return (0);
}
