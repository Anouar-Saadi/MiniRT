/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_squares.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 10:06:55 by asaadi            #+#    #+#             */
/*   Updated: 2020/12/02 17:56:47 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	inters_ray_support_plan(t_plane *plane,
		t_data *data, t_ray *ray)
{
	t_coord		dist_ray_pl;
	double		dist_dot_n;
	double		d_dot_n;

	dist_ray_pl = sub_vec(&ray->origin, &plane->point_at_pl);
	d_dot_n = vec_dot(ray->direction, plane->plane_norm);
	if (d_dot_n != 0)
	{
		dist_dot_n = vec_dot(dist_ray_pl, plane->plane_norm);
		data->rec.t = -dist_dot_n / d_dot_n;
		if (data->rec.t < 0)
			return (0);
		return (1);
	}
	return (0);
}

double			inters_ray_square(t_data *data, t_objects *obj, t_ray *ray)
{
	t_plane	plane;
	t_coord	tmp;
	double	i;
	t_coord	point;

	plane.point_at_pl = obj->square.sq_center;
	plane.plane_norm = obj->square.or_vec;
	if ((i = inters_ray_support_plan(&plane, data, ray)) == 1)
	{
		point = point_of_hit(data->rec.t, *ray);
		tmp = sub_vec(&obj->square.sq_center, &point);
		if (fabs(tmp.x) <= (obj->square.size_side / 2) &&
				fabs(tmp.y) <= (obj->square.size_side / 2) &&
				fabs(tmp.z) <= (obj->square.size_side / 2))
			return (1.0);
		return (0);
	}
	return (0);
}
