/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rotation_trans.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 17:41:58 by asaadi            #+#    #+#             */
/*   Updated: 2020/12/03 10:25:47 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_trans_sphere(t_data *data, t_objects *obj, char **s_line)
{
	char **s_arg;

	if (ft_count_arguments(s_line) > 4)
	{
		s_arg = ft_split(s_line[4], ',');
		if (ft_count_arguments(s_arg) != 3)
			ft_put_error(data, "Please check the rotation in sphere.");
		data->translation = parser_vector(s_arg);
		obj->sphere.center = ft_make_trans(obj->sphere.center,
				data->translation);
		ft_free_split(s_arg);
	}
}

void	ft_translation_rotatation_cylinder(t_data *data,
		t_objects *obj, char **s_line)
{
	char **s_arg;

	if (ft_count_arguments(s_line) > 6)
	{
		if (s_line[6])
		{
			s_arg = ft_split(s_line[6], ',');
			if (ft_count_arguments(s_arg) != 3)
				ft_put_error(data, "Please check the rotation in cylinder.");
			data->rotation = parser_vector(s_arg);
			obj->cylinder.normal = ft_make_rotat(data->rotation,
					obj->cylinder.normal);
			ft_free_split(s_arg);
		}
		if (s_line[7])
		{
			s_arg = ft_split(s_line[7], ',');
			if (ft_count_arguments(s_arg) != 3)
				ft_put_error(data, "Please check the translation in cylinder.");
			data->translation = parser_vector(s_arg);
			obj->cylinder.pos = ft_make_trans(obj->cylinder.pos,
					data->translation);
			ft_free_split(s_arg);
		}
	}
}

void	ft_translation_rotatation_plane(t_data *data,
		t_objects *obj, char **s_line)
{
	char **s_arg;

	if (ft_count_arguments(s_line) > 4)
	{
		if (s_line[4])
		{
			s_arg = ft_split(s_line[4], ',');
			if (ft_count_arguments(s_arg) != 3)
				ft_put_error(data, "Please check the rotation plane.");
			data->rotation = parser_vector(s_arg);
			obj->plane.plane_norm = ft_make_rotat(data->rotation,
					obj->plane.plane_norm);
			ft_free_split(s_arg);
		}
		if (s_line[5])
		{
			s_arg = ft_split(s_line[5], ',');
			if (ft_count_arguments(s_arg) != 3)
				ft_put_error(data, "Please check the translation plane.");
			data->translation = parser_vector(s_arg);
			obj->plane.point_at_pl = ft_make_trans(obj->plane.point_at_pl,
					data->translation);
			ft_free_split(s_arg);
		}
	}
}

void	ft_translation_rotatation_square(t_data *data,
		t_objects *obj, char **s_line)
{
	char **s_arg;

	if (ft_count_arguments(s_line) > 5)
	{
		if (s_line[4])
		{
			s_arg = ft_split(s_line[4], ',');
			if (ft_count_arguments(s_arg) != 3)
				ft_put_error(data, "Please check the rotation square.");
			data->rotation = parser_vector(s_arg);
			obj->square.or_vec = ft_make_rotat(data->rotation,
					obj->square.or_vec);
			ft_free_split(s_arg);
		}
		if (s_line[5])
		{
			s_arg = ft_split(s_line[5], ',');
			if (ft_count_arguments(s_arg) != 3)
				ft_put_error(data, "Please check the translation square.");
			data->translation = parser_vector(s_arg);
			obj->square.sq_center = ft_make_trans(obj->square.sq_center,
					data->translation);
			ft_free_split(s_arg);
		}
	}
}

void	check_rotation_translation_objs(t_data *data,
		t_objects *obj, char **s_line)
{
	char **s_arg;

	if (obj->obj_type == SP)
		ft_trans_sphere(data, obj, s_line);
	else if (obj->obj_type == CY)
		ft_translation_rotatation_cylinder(data, obj, s_line);
	else if (obj->obj_type == PL)
		ft_translation_rotatation_plane(data, obj, s_line);
	else if (obj->obj_type == SQ)
		ft_translation_rotatation_square(data, obj, s_line);
	else if (obj->obj_type == TR)
		if (ft_count_arguments(s_line) == 6)
		{
			s_arg = ft_split(s_line[5], ',');
			if (ft_count_arguments(s_arg) != 3)
				ft_put_error(data, "Please check the translation triangle.");
			data->translation = parser_vector(s_arg);
			obj->triangle.first_point = ft_make_trans(obj->triangle.first_point,
					data->translation);
			obj->triangle.second_point =
				ft_make_trans(obj->triangle.second_point, data->translation);
			obj->triangle.third_point = ft_make_trans(obj->triangle.third_point,
					data->translation);
			ft_free_split(s_arg);
		}
}
