/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_pixels_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:05:47 by asaadi            #+#    #+#             */
/*   Updated: 2020/12/03 14:13:47 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_color	get_col_obj(t_objects *obj)
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

t_color			color_final_pixel(t_data *data, t_objects *obj,
		t_color deff_col, t_color spec_col)
{
	t_color pixel_col;
	t_color amb_col;
	t_color	obj_col;

	pixel_col = get_color(0, 0, 0);
	amb_col = ambient_light(data);
	obj_col = get_col_obj(obj);
	pixel_col.r = obj_col.r * (amb_col.r + deff_col.r) + spec_col.r;
	pixel_col.g = obj_col.g * (amb_col.g + deff_col.g) + spec_col.g;
	pixel_col.b = obj_col.b * (amb_col.b + deff_col.b) + spec_col.b;
	min_max_color(&pixel_col);
	return (pixel_col);
}

static double	get_shine_factor(t_objects *obj)
{
	double shine_factor;

	shine_factor = 0;
	if (obj->obj_type == SP)
		shine_factor = 250;
	else if (obj->obj_type == PL)
		shine_factor = 2000;
	else if (obj->obj_type == SQ)
		shine_factor = 2000;
	else if (obj->obj_type == TR)
		shine_factor = 2000;
	else if (obj->obj_type == CY)
		shine_factor = 1000;
	return (shine_factor);
}

t_color			get_deffuse_at_point(t_data *data,
		t_light *tmp_light, t_color deff0)
{
	t_color deff1;

	if (data->shadow == 1)
	{
		deff1 = get_color(0, 0, 0);
		deff0 = add_color(deff0, deff1);
	}
	else if (data->shadow == 0)
	{
		deff1 = deffuse_light(data, tmp_light);
		deff0 = add_color(deff0, deff1);
	}
	return (deff0);
}

t_color			get_spec_at_point(t_data *data, t_light *tmp_light,
		t_objects *obj, t_color spec0)
{
	t_color	spec1;
	double	shine_factor;

	if (data->shadow == 1)
	{
		spec1 = get_color(0, 0, 0);
		spec0 = add_color(spec0, spec1);
	}
	else if (data->shadow == 0)
	{
		shine_factor = get_shine_factor(obj);
		spec1 = specular_light(data, tmp_light, shine_factor);
		spec0 = add_color(spec0, spec1);
	}
	return (spec0);
}
