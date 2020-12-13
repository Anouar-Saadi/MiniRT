/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 09:08:33 by asaadi            #+#    #+#             */
/*   Updated: 2020/12/03 09:41:21 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	parser_cylinder_2(t_data *data, char **split_line, t_objects *obj)
{
	char **split_arg;

	split_arg = ft_split(split_line[3], ',');
	check_parse_color(data, split_arg);
	obj->cylinder.col = parser_color(split_arg);
	ft_free_split(split_arg);
	if (ft_strtod(split_line[4]) < 0 || ft_strchr(split_line[4], ','))
		ft_put_error(data, "Check cylinder diameter.");
	obj->cylinder.diameter = ft_strtod(split_line[4]);
	if (ft_strtod(split_line[5]) < 0 || ft_strchr(split_line[5], ','))
		ft_put_error(data, "Check cylinder height.");
	obj->cylinder.height = ft_strtod(split_line[5]);
}

void		parser_cylinder(t_data *data, char *line)
{
	char		**split_line;
	char		**split_arg;
	t_objects	*obj;

	if (!(obj = malloc(sizeof(t_objects))))
		ft_put_error(data, "Allocation error.");
	obj->obj_type = CY;
	split_line = ft_split(line, ' ');
	if (ft_count_arguments(split_line) < 6
			|| ft_count_arguments(split_line) > 8)
		ft_put_error(data, "Check the cylinder infos in scene.");
	split_arg = ft_split(split_line[1], ',');
	check_coord_vec(data, split_arg);
	obj->cylinder.pos = parser_vector(split_arg);
	split_arg = ft_split(split_line[2], ',');
	check_coord_normal(data, split_arg);
	obj->cylinder.normal = parser_vector(split_arg);
	ft_free_split(split_arg);
	parser_cylinder_2(data, split_line, obj);
	check_rotation_translation_objs(data, obj, split_line);
	obj->next = NULL;
	ft_free_split(split_line);
	ft_add_objects(&data->objects, obj);
}

static void	parser_triangle_2(t_data *data, char **split_line, t_objects *obj)
{
	char **split_arg;

	split_arg = ft_split(split_line[1], ',');
	check_coord_vec(data, split_arg);
	obj->triangle.first_point = parser_vector(split_arg);
	ft_free_split(split_arg);
	split_arg = ft_split(split_line[2], ',');
	check_coord_vec(data, split_arg);
	obj->triangle.second_point = parser_vector(split_arg);
	split_arg = ft_split(split_line[3], ',');
	check_coord_vec(data, split_arg);
	obj->triangle.third_point = parser_vector(split_arg);
	ft_free_split(split_arg);
	split_arg = ft_split(split_line[4], ',');
	check_parse_color(data, split_arg);
	obj->triangle.tr_col = parser_color(split_arg);
	ft_free_split(split_arg);
}

void		parser_triangle(t_data *data, char *line)
{
	char		**split_line;
	t_objects	*obj;

	if (!(obj = malloc(sizeof(t_objects))))
		ft_put_error(data, "Allocation error.");
	obj->obj_type = TR;
	split_line = ft_split(line, ' ');
	if (ft_count_arguments(split_line) < 5
			|| ft_count_arguments(split_line) > 6)
		ft_put_error(data, "Check the triangle line.");
	parser_triangle_2(data, split_line, obj);
	check_rotation_translation_objs(data, obj, split_line);
	ft_free_split(split_line);
	obj->next = NULL;
	ft_add_objects(&data->objects, obj);
}

int			ft_count_arguments(char **s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
