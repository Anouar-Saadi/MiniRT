/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinders.k[2]                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:42:56 by asaadi            #+#    #+#             */
/*   Updated: 2020/11/19 11:47:53 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* 
    k[0]   = D|D - (D|V)^2
    k[1]/2 = D|oc - (D|V)*(oc|V)
    k[2]   = oc|oc - (oc|V)^2 - r*r
    k[3]   = delta
*/

static double check_the_solutions(t_data *data, double m, double t)
{
    data->rec.t = t;
    data->rec.m = m;
    return (1);
}

double inters_ray_cylinder(t_data *data, t_objects *obj, t_ray *ray)
{
    double k[4];
    double t[2];
    double m[2];
    t_coord oc;

    oc = sub_vec(&ray->origin, &obj->cylinder.pos);
    k[0] = vec_dot(ray->direction, ray->direction) - pow(vec_dot(ray->direction, obj->cylinder.normal), 2);
    k[1] = 2 * (vec_dot(ray->direction, oc) - (vec_dot(ray->direction, obj->cylinder.normal) * vec_dot(oc, obj->cylinder.normal)));
    k[2] = vec_dot(oc, oc) - pow(vec_dot(oc, obj->cylinder.normal), 2) - pow(obj->cylinder.diameter / 2, 2);
    k[3] = k[1] * k[1] - 4 * k[0] * k[2];
    if (k[3] < 0.0)
        return (0);
    t[0] = (-k[1] - sqrt(k[3])) / (2.0 * k[0]);
    t[1] = (-k[1] + sqrt(k[3])) / (2.0 * k[0]);
    m[0] = vec_dot(ray->direction, obj->cylinder.normal) * t[0] + vec_dot(oc, obj->cylinder.normal);
    m[1] = vec_dot(ray->direction, obj->cylinder.normal) * t[1] + vec_dot(oc, obj->cylinder.normal);
    if (m[0] >= 0 && m[0] <= obj->cylinder.height)
        return (check_the_solutions(data, m[0], t[0]));
    else if (m[1] >= 0 && m[1] <= obj->cylinder.height)
        return (check_the_solutions(data, m[1], t[1]));
    return (0);
}
