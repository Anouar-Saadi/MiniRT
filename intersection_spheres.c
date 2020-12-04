/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_spheres.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:17:18 by asaadi            #+#    #+#             */
/*   Updated: 2020/11/19 18:23:09 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
**	Intersection between a ray and a sphere
**	a*t^2 + b*t + c = 0
**	k[0] == a
**	k[1] == b
**	k[2] == c
**	k[3] == delta;
*/

double	inters_ray_sphere(t_data *data, t_objects *object, t_ray *ray)
{
	double	k[4];
	t_coord	oc;
	double	t[2];

	k[0] = vec_dot(ray->direction, ray->direction);
	oc = sub_vec(&ray->origin, &object->sphere.center);
	k[1] = 2.0 * vec_dot(ray->direction, oc);
	k[2] = vec_dot(oc, oc) - (object->sphere.radius * object->sphere.radius);
	k[3] = k[1] * k[1] - 4 * k[0] * k[2];
	if (k[3] < 0.0)
		return (0);
	t[0] = (-k[1] - sqrt(k[3])) / (2.0 * k[0]);
	t[1] = (-k[1] + sqrt(k[3])) / (2.0 * k[0]);
	data->rec.t = (t[0] > 0) ? t[0] : t[1];
	if (data->rec.t < 0)
		return (0);
	return (1.0);
}
