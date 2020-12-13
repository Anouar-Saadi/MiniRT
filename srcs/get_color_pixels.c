/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_pixels.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 09:46:37 by asaadi            #+#    #+#             */
/*   Updated: 2020/12/07 08:38:24 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_the_light_at_point(t_data *data,
		t_light *tmp_light, t_objects *obj)
{
	double	d_light;
	t_ray	ray_shad;

	data->rec.light_ray = sub_vec(&tmp_light->position, &data->rec.hit_point);
	d_light = lenght(data->rec.light_ray);
	data->rec.light_ray = unit_vector(data->rec.light_ray);
	ray_shad.origin = (vect_scal(0.0001, data->rec.normal));
	ray_shad.origin = vec_add(&ray_shad.origin, &data->rec.hit_point);
	ray_shad.direction = data->rec.light_ray;
	if (vec_dot(data->rec.normal, data->ray.direction) > 0)
		data->rec.normal = vect_scal(-1, data->rec.normal);
	if (find_the_closest_obj(data, &ray_shad, obj) != NULL
			&& (data->rec.t_closest < d_light))
		return (1);
	else
		return (0);
}

t_color		compte_lighting(t_data *data, t_objects *obj)
{
	t_light	*tmp_lights;
	t_color	deff_col;
	t_color	spec_col;

	deff_col = get_color(0, 0, 0);
	spec_col = get_color(0, 0, 0);
	tmp_lights = data->light;
	while (tmp_lights != NULL)
	{
		if (check_the_light_at_point(data, tmp_lights, obj))
		{
			data->shadow = 1;
			deff_col = get_deffuse_at_point(data, tmp_lights, deff_col);
			spec_col = get_spec_at_point(data, tmp_lights, obj, spec_col);
		}
		else
		{
			data->shadow = 0;
			deff_col = get_deffuse_at_point(data, tmp_lights, deff_col);
			spec_col = get_spec_at_point(data, tmp_lights, obj, spec_col);
		}
		tmp_lights = tmp_lights->next;
	}
	return (color_final_pixel(data, obj, deff_col, spec_col));
}

void		ft_init_hit_record(t_hit_rec *hit)
{
	hit->t = -1;
	hit->t_closest = -1;
	hit->m = 0;
	hit->hit_point = new_vector(0.0, 0.0, 0.0);
	hit->normal = new_vector(0.0, 0.0, 0.0);
	hit->light_ray = new_vector(0.0, 0.0, 0.0);
	hit->view = new_vector(0.0, 0.0, 0.0);
}

t_color		scene_trace(t_data *data)
{
	t_color		background_col;
	t_objects	*closest_obj;

	background_col = get_color(0, 0, 0);
	closest_obj = NULL;
	if (data->objects)
	{
		ft_init_hit_record(&data->rec);
		closest_obj = find_the_closest_obj(data, &data->ray, NULL);
		if (!closest_obj)
			return (background_col);
		data->rec.hit_point = point_of_hit(data->rec.t_closest, data->ray);
		calcul_normal_at_hit_point(data, closest_obj);
		return (compte_lighting(data, closest_obj));
	}
	return (background_col);
}
