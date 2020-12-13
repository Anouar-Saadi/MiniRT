/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_illumination.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 12:42:29 by asaadi            #+#    #+#             */
/*   Updated: 2020/12/02 17:59:25 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	ambient_light(t_data *data)
{
	t_color	obj_amb;

	obj_amb.r = data->illum.ka * (data->illum.amb_col.r / 255.0);
	obj_amb.g = data->illum.ka * (data->illum.amb_col.g / 255.0);
	obj_amb.b = data->illum.ka * (data->illum.amb_col.b / 255.0);
	return (obj_amb);
}

t_color	deffuse_light(t_data *data, t_light *light)
{
	double	n_dot_l;
	t_color	obj_deff;

	n_dot_l = vec_dot(data->rec.normal, data->rec.light_ray);
	if (n_dot_l < 0.0)
		return (get_color(0, 0, 0));
	obj_deff.r = light->kd * (light->intensity.r / 255.0) * n_dot_l;
	obj_deff.g = light->kd * (light->intensity.g / 255.0) * n_dot_l;
	obj_deff.b = light->kd * (light->intensity.b / 255.0) * n_dot_l;
	return (obj_deff);
}

t_color	specular_light(t_data *data, t_light *light, double shine_factor)
{
	double	h_dot_n;
	t_color	spec_obj;
	t_coord	half;

	data->rec.view = sub_vec(&data->ray.origin, &data->rec.hit_point);
	data->rec.view = unit_vector(data->rec.view);
	half = vec_add(&data->rec.view, &data->rec.light_ray);
	half = unit_vector(half);
	h_dot_n = vec_dot(half, data->rec.normal);
	if (h_dot_n < 0.0)
		return (get_color(0, 0, 0));
	spec_obj.r = (light->intensity.r / 255.0) * pow(h_dot_n, shine_factor);
	spec_obj.g = (light->intensity.g / 255.0) * pow(h_dot_n, shine_factor);
	spec_obj.b = (light->intensity.b / 255.0) * pow(h_dot_n, shine_factor);
	return (spec_obj);
}
