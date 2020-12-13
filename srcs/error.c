/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 10:41:54 by asaadi            #+#    #+#             */
/*   Updated: 2020/12/02 18:37:08 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_put_error(t_data *data, char *str)
{
	write(1, "error\n", 6);
	write(1, str, ft_strlen(str));
	ft_free_data_scene(data);
	exit(1);
}

void	check_parse_color(t_data *data, char **split2)
{
	if (ft_count_arguments(split2) != 3)
		ft_put_error(data, "The color should have a RGB.");
	if (ft_strtod(split2[0]) < 0 || ft_strtod(split2[1]) < 0
			|| ft_strtod(split2[2]) < 0 || ft_strtod(split2[0]) > 255
			|| ft_strtod(split2[1]) > 255 || ft_strtod(split2[2]) > 255)
		ft_put_error(data, "The RGB should be between 0 and 255.");
}

void	check_coord_vec(t_data *data, char **split)
{
	if (ft_count_arguments(split) != 3)
		ft_put_error(data, "The positon should have a X , Y and Z.");
}

void	check_coord_normal(t_data *data, char **split)
{
	check_coord_vec(data, split);
	if (ft_strtod(split[0]) < -1 || ft_strtod(split[1]) < -1
			|| ft_strtod(split[2]) < -1 || ft_strtod(split[0]) > 1
			|| ft_strtod(split[1]) > 1 || ft_strtod(split[2]) > 1)
		ft_put_error(data, "The orientation should be between -1 and 1.");
}

void	ft_check_scene(t_data *data)
{
	if (!data->mlx.x_res && !data->mlx.y_res)
		ft_put_error(data, "No Resolution in the scene.");
	if (data->illum.ka == -1)
		ft_put_error(data, "No ambient lighting in the scene.");
	if (data->camera == NULL)
		ft_put_error(data, "You must specify at least one camera.");
}
