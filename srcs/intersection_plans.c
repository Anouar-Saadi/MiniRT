/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_plans.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:47:49 by asaadi            #+#    #+#             */
/*   Updated: 2020/12/02 17:53:49 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	inters_ray_plan(t_data *data, t_objects *obj, t_ray *ray)
{
	t_coord	dist_ray_pl;
	double	dist_dot_n;
	double	d_dot_n;

	dist_ray_pl = sub_vec(&ray->origin, &obj->plane.point_at_pl);
	dist_dot_n = vec_dot(dist_ray_pl, obj->plane.plane_norm);
	d_dot_n = vec_dot(ray->direction, obj->plane.plane_norm);
	if (d_dot_n != 0.0 && ((d_dot_n > 0 && dist_dot_n < 0)
				|| (d_dot_n < 0 && dist_dot_n > 0)))
	{
		data->rec.t = -(dist_dot_n / d_dot_n);
		if (data->rec.t < 0.0)
			return (0);
		return (1.0);
	}
	return (0);
}
