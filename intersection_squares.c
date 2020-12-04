/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_squares.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 10:06:55 by asaadi            #+#    #+#             */
/*   Updated: 2020/11/19 11:51:48 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double inters_ray_support_plan(t_plane *plane, t_data *data, t_objects *obj, t_ray *ray)
{
    t_coord dist_ray_pl;
    double dist_dot_n;
    double d_dot_n;

    dist_ray_pl = sub_vec(&ray->origin, &plane->point_at_pl);
    dist_dot_n = vec_dot(dist_ray_pl, plane->plane_norm);
    d_dot_n = vec_dot(ray->direction, plane->plane_norm);
    if (d_dot_n < 0)
        obj->square.or_vec = vect_scal(-1, obj->square.or_vec);
    if (d_dot_n != 0.0 && ((d_dot_n > 0 && dist_dot_n < 0) ||
                           (d_dot_n < 0 && dist_dot_n > 0)))
    {
        data->rec.t = -(dist_dot_n / d_dot_n);
        if (data->rec.t < 0.0)
            return (0);
        return (1.0);
    }
    return (0);
}

double inters_ray_square(t_data *data, t_objects *obj, t_ray *ray)
{
    t_plane plane;
    t_coord tmp;
    double i;

    plane.point_at_pl = obj->square.sq_center;
    plane.plane_norm = obj->square.or_vec;
    if ((i = inters_ray_support_plan(&plane, data, obj, ray)) > 0)
    {
        tmp = sub_vec(&obj->square.sq_center, &data->rec.hit_point);
        if (fabs(tmp.x) <= (obj->square.size_side / 2) &&
            fabs(tmp.y) <= (obj->square.size_side / 2) &&
            fabs(tmp.z) <= (obj->square.size_side / 2))
            return (1.0);
        return (0);
    }
    return (0);
}
