/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:46:04 by asaadi            #+#    #+#             */
/*   Updated: 2020/12/03 09:37:16 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		parser_sphere(t_data *data, char *line)
{
	char		**split_line;
	char		**split_arg;
	t_objects	*obj;

	if (!(obj = malloc(sizeof(t_objects))))
		ft_put_error(data, "Allocation error.");
	obj->obj_type = SP;
	split_line = ft_split(line, ' ');
	if (ft_count_arguments(split_line) < 4
			|| ft_count_arguments(split_line) > 5)
		ft_put_error(data, "Please check the sphere infos in scene.");
	split_arg = ft_split(split_line[1], ',');
	check_coord_vec(data, split_arg);
	obj->sphere.center = parser_vector(split_arg);
	if (ft_strtod(split_line[2]) < 0 || ft_strchr(split_line[2], ','))
		ft_put_error(data, "Check the radius sphere.");
	obj->sphere.radius = ft_strtod(split_line[2]);
	split_arg = ft_split(split_line[3], ',');
	check_parse_color(data, split_arg);
	obj->sphere.s_color = parser_color(split_arg);
	check_rotation_translation_objs(data, obj, split_line);
	ft_free_split(split_line);
	obj->next = NULL;
	ft_add_objects(&data->objects, obj);
}

void		parser_plane(t_data *data, char *line)
{
	char		**split_line;
	char		**split_arg;
	t_objects	*obj;

	if (!(obj = malloc(sizeof(t_objects))))
		ft_put_error(data, "Allocation error.");
	obj->obj_type = PL;
	split_line = ft_split(line, ' ');
	if (ft_count_arguments(split_line) < 4
			&& ft_count_arguments(split_line) > 6)
		ft_put_error(data, "Check plane line in scene.");
	split_arg = ft_split(split_line[1], ',');
	check_coord_vec(data, split_arg);
	obj->plane.point_at_pl = parser_vector(split_arg);
	split_arg = ft_split(split_line[2], ',');
	check_coord_normal(data, split_arg);
	obj->plane.plane_norm = parser_vector(split_arg);
	split_arg = ft_split(split_line[3], ',');
	check_parse_color(data, split_arg);
	obj->plane.pl_col = parser_color(split_arg);
	check_rotation_translation_objs(data, obj, split_line);
	ft_free_split(split_line);
	obj->next = NULL;
	ft_add_objects(&data->objects, obj);
}

static void	parser_square_2(t_data *data, char **split_line, t_objects *obj)
{
	char **split_arg;

	if (ft_strtod(split_line[3]) < 0 || ft_strchr(split_line[3], ','))
		ft_put_error(data, "Check the square size_side it's mybe negative.");
	obj->square.size_side = ft_strtod(split_line[3]);
	split_arg = ft_split(split_line[4], ',');
	check_parse_color(data, split_arg);
	obj->square.sq_col = parser_color(split_arg);
}

void		parser_square(t_data *data, char *line)
{
	char		**split_line;
	char		**split_arg;
	t_objects	*obj;

	if (!(obj = malloc(sizeof(t_objects))))
		ft_put_error(data, "Allocation error.");
	obj->obj_type = SQ;
	split_line = ft_split(line, ' ');
	if (ft_count_arguments(split_line) < 5
			|| ft_count_arguments(split_line) > 7)
		ft_put_error(data, "Check the square struct in scene.");
	split_arg = ft_split(split_line[1], ',');
	check_coord_vec(data, split_arg);
	obj->square.sq_center = parser_vector(split_arg);
	split_arg = ft_split(split_line[2], ',');
	check_coord_normal(data, split_arg);
	obj->square.or_vec = parser_vector(split_arg);
	parser_square_2(data, split_line, obj);
	check_rotation_translation_objs(data, obj, split_line);
	ft_free_split(split_line);
	obj->next = NULL;
	ft_add_objects(&data->objects, obj);
}
