/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 17:30:43 by asaadi            #+#    #+#             */
/*   Updated: 2020/12/03 09:45:16 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_resolution(t_data *data)
{
	int width;
	int height;

	mlx_get_screen_size(data->mlx.mlx_ptr, &width, &height);
	if (data->mlx.x_res > width)
		data->mlx.x_res = width;
	if (data->mlx.y_res > height)
		data->mlx.y_res = height;
}

void	parser_resolution(t_data *data, char *line)
{
	char **split_line;

	if (data->mlx.x_res != 0 || data->mlx.y_res != 0)
		ft_put_error(data, "You can't use the resolution twice in scene.");
	split_line = ft_split(line, ' ');
	if (ft_count_arguments(split_line) != 3 || ft_strchr(*split_line, ','))
		ft_put_error(data, "The resolution have a width and height.");
	if (ft_strtod(split_line[1]) <= 0 || ft_strtod(split_line[2]) <= 0.0)
		ft_put_error(data, "The resolution can't be negative or null");
	data->mlx.x_res = ft_strtod(split_line[1]);
	data->mlx.y_res = ft_strtod(split_line[2]);
	check_resolution(data);
	ft_free_split(split_line);
}

void	parser_ambiant_light(t_data *data, char *line)
{
	char	**split_line;
	char	**split_arg;

	if (data->illum.amb_col.r != 0 || data->illum.amb_col.g != 0
			|| data->illum.amb_col.b != 0 || data->illum.ka != -1)
		ft_put_error(data, "The ambiant lighting use once in scene.");
	split_line = ft_split(line, ' ');
	if (ft_count_arguments(split_line) != 3)
		ft_put_error(data, "The ambiant lighting have a color and ratio.");
	if (ft_strchr(split_line[1], ','))
		ft_put_error(data, "Check the ambient ratio.");
	if (ft_strtod(split_line[1]) < 0 || ft_strtod(split_line[1]) > 1
			|| ft_strchr(split_line[1], ','))
		ft_put_error(data, "Check the ambient ratio.");
	data->illum.ka = ft_strtod(split_line[1]);
	split_arg = ft_split(split_line[2], ',');
	check_parse_color(data, split_arg);
	data->illum.amb_col = parser_color(split_arg);
	ft_free_split(split_arg);
	ft_free_split(split_line);
}

void	parser_light(t_data *data, char *line)
{
	t_light	*light;
	char	**split_line;
	char	**split_arg;

	if (!(light = malloc(sizeof(t_light))))
		ft_put_error(data, "Allocation error.");
	split_line = ft_split(line, ' ');
	if (ft_count_arguments(split_line) < 4
			|| ft_count_arguments(split_line) > 5)
		ft_put_error(data, "Check the light scene.");
	if (ft_strtod(split_line[2]) < 0 || ft_strtod(split_line[2]) > 1
			|| ft_strchr(split_line[2], ','))
		ft_put_error(data, "check the brightnes ratio at light.");
	light->kd = ft_strtod(split_line[2]);
	split_arg = ft_split(split_line[1], ',');
	check_coord_vec(data, split_arg);
	light->position = parser_vector(split_arg);
	split_arg = ft_split(split_line[3], ',');
	check_parse_color(data, split_arg);
	light->intensity = parser_color(split_arg);
	ft_free_split(split_arg);
	check_translation_light(data, light, split_line);
	ft_free_split(split_line);
	light->next = NULL;
	ft_add_lights(&data->light, light);
}

void	parser_camera(t_data *data, char *line)
{
	t_camera	*camera;
	char		**s_line;
	char		**split_arg;

	if (!(camera = malloc(sizeof(t_camera))))
		ft_put_error(data, "Allocation error.");
	s_line = ft_split(line, ' ');
	if (ft_count_arguments(s_line) < 4 || ft_count_arguments(s_line) > 6)
		ft_put_error(data, "Please! Check the camera in the scene.");
	split_arg = ft_split(s_line[1], ',');
	check_coord_vec(data, split_arg);
	camera->eye = parser_vector(split_arg);
	split_arg = ft_split(s_line[2], ',');
	check_coord_normal(data, split_arg);
	camera->look_at = parser_vector(split_arg);
	ft_free_split(split_arg);
	if (ft_strtod(s_line[3]) < 0 || ft_strtod(s_line[3]) > 180
			|| ft_strchr(s_line[3], ','))
		ft_put_error(data, "Please! Check the field of view in camera.");
	camera->fov = ft_strtod(s_line[3]);
	check_rotation_translation_in_camera(data, camera, s_line);
	camera->next = NULL;
	camera->previous = NULL;
	ft_free_split(s_line);
	ft_add_cameras(&data->camera, camera);
}
