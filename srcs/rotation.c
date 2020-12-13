/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 03:21:57 by asaadi            #+#    #+#             */
/*   Updated: 2020/12/04 08:53:38 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coord		x_rotation(t_coord normal, double tetha)
{
	t_coord vec_to_rotate;

	tetha = tetha * (M_PI / 180);
	vec_to_rotate.x = normal.x;
	vec_to_rotate.y = normal.y * cos(tetha) - normal.z * sin(tetha);
	vec_to_rotate.z = normal.y * sin(tetha) + normal.z * cos(tetha);
	return (vec_to_rotate);
}

t_coord		y_rotation(t_coord normal, double tetha)
{
	t_coord vec_to_rotate;

	tetha = tetha * (M_PI / 180);
	vec_to_rotate.x = normal.x * cos(tetha) + normal.z * sin(tetha);
	vec_to_rotate.y = normal.y;
	vec_to_rotate.z = normal.z * cos(tetha) - normal.x * sin(tetha);
	return (vec_to_rotate);
}

t_coord		z_rotation(t_coord normal, double tetha)
{
	t_coord vec_to_rotate;

	tetha = tetha * (M_PI / 180);
	vec_to_rotate.x = normal.x * cos(tetha) - (normal.y * sin(tetha));
	vec_to_rotate.y = normal.x * sin(tetha) + normal.y * cos(tetha);
	vec_to_rotate.z = normal.z;
	return (vec_to_rotate);
}

t_coord		ft_make_rotat(t_coord rot, t_coord normal)
{
	t_coord new_coord;

	new_coord.x = normal.x;
	new_coord.y = normal.y;
	new_coord.z = normal.z;
	new_coord = x_rotation(new_coord, rot.x);
	new_coord = y_rotation(new_coord, rot.y);
	new_coord = z_rotation(new_coord, rot.z);
	new_coord = unit_vector(new_coord);
	return (new_coord);
}

void		check_rotation_translation_in_camera(t_data *data,
		t_camera *cam, char **s_line)
{
	char **s_arg;

	if (ft_count_arguments(s_line) > 4)
	{
		if (s_line[4])
		{
			s_arg = ft_split(s_line[4], ',');
			if (ft_count_arguments(s_arg) != 3)
				ft_put_error(data, "Please Check the rotation in camera.");
			data->rotation = parser_vector(s_arg);
			cam->look_at = ft_make_rotat(data->rotation, cam->look_at);
		}
		if (s_line[5])
		{
			s_arg = ft_split(s_line[5], ',');
			if (ft_count_arguments(s_arg) != 3)
				ft_put_error(data, "Please Check the translation in camera.");
			data->translation = parser_vector(s_arg);
			cam->eye = ft_make_trans(cam->eye, data->translation);
		}
	}
}
