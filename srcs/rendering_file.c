/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 08:37:07 by asaadi            #+#    #+#             */
/*   Updated: 2020/12/04 13:50:40 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	trace_ray(t_data *data, t_camera *camera)
{
	int		i;
	int		j;
	t_color	col;
	int		t;
	int		color[3];

	ft_camera_viewport(data, camera);
	j = -1;
	while (++j < data->mlx.y_res)
	{
		i = -1;
		while (++i < data->mlx.x_res)
		{
			col = get_color(0, 0, 0);
			data->ray = get_ray(data, camera, i, j);
			col = scene_trace(data);
			color[0] = (int)(255.00 * col.r);
			color[1] = (int)(255.00 * col.g);
			color[2] = (int)(255.00 * col.b);
			t = j * data->mlx.x_res + i;
			data->img.addr[t] =
				((color[0] << 16) | (color[1] << 8) | (color[2] << 0));
		}
	}
}

void	wich_camera(int button, t_data *data)
{
	t_camera		*camera;
	static t_camera	*tmp_cam;

	camera = NULL;
	if (tmp_cam == NULL)
		tmp_cam = data->camera;
	if (button == NEXT_CAM && tmp_cam->next != NULL)
	{
		camera = tmp_cam->next;
		tmp_cam = camera;
		trace_ray(data, camera);
		mlx_put_image_to_window(data->mlx.mlx_ptr,
				data->mlx.win_ptr, data->img.img, 0, 0);
	}
	if (button == PREV_CAM && tmp_cam->previous != NULL)
	{
		camera = tmp_cam->previous;
		tmp_cam = camera;
		trace_ray(data, camera);
		mlx_put_image_to_window(data->mlx.mlx_ptr,
				data->mlx.win_ptr, data->img.img, 0, 0);
	}
}

int		key_press(int button, t_data *data)
{
	if (button == ESC)
	{
		ft_free_data_scene(data);
		exit(0);
	}
	if (button == NEXT_CAM || button == PREV_CAM)
		wich_camera(button, data);
	return (0);
}

void	ft_create_the_window(t_data *data, char *name_program)
{
	data->mlx.mlx_ptr = mlx_init();
	data->mlx.win_ptr = mlx_new_window(data->mlx.mlx_ptr,
			data->mlx.x_res, data->mlx.y_res, name_program);
	data->img.img = mlx_new_image(data->mlx.mlx_ptr,
			data->mlx.x_res, data->mlx.y_res);
	data->img.addr = (int *)mlx_get_data_addr(data->img.img,
			&data->img.bits_per_pixel, &data->img.size_line, &data->img.endian);
	trace_ray(data, data->camera);
	mlx_put_image_to_window(data->mlx.mlx_ptr,
			data->mlx.win_ptr, data->img.img, 0, 0);
	mlx_hook(data->mlx.win_ptr, 2, 0, key_press, data);
	mlx_hook(data->mlx.win_ptr, 17, 0, ft_close, data);
	mlx_loop(data->mlx.mlx_ptr);
	ft_free_data_scene(data);
	exit(0);
}

void	ft_create_image(t_data *data)
{
	data->mlx.mlx_ptr = mlx_init();
	data->img.img = mlx_new_image(data->mlx.mlx_ptr,
			data->mlx.x_res, data->mlx.y_res);
	data->img.addr = (int *)mlx_get_data_addr(data->img.img,
			&data->img.bits_per_pixel, &data->img.size_line, &data->img.endian);
	trace_ray(data, data->camera);
	ft_create_image_bmp(data);
	ft_free_data_scene(data);
	exit(0);
}
