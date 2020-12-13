/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 08:28:19 by asaadi            #+#    #+#             */
/*   Updated: 2020/12/03 10:24:26 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coord	ft_make_trans(t_coord pos_to_trans, t_coord translation)
{
	t_coord new_pos;

	new_pos.x = pos_to_trans.x + translation.x;
	new_pos.y = pos_to_trans.y + translation.y;
	new_pos.z = pos_to_trans.z + translation.z;
	return (new_pos);
}

void	check_translation_light(t_data *data, t_light *light, char **s_line)
{
	char **s_arg;

	if (ft_count_arguments(s_line) == 5)
	{
		s_arg = ft_split(s_line[4], ',');
		check_coord_vec(data, s_arg);
		data->translation = parser_vector(s_arg);
		light->position = ft_make_trans(light->position,
				data->translation);
	}
}
