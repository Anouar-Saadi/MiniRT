/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:10:11 by asaadi            #+#    #+#             */
/*   Updated: 2020/11/19 12:32:08 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void trace_ray(t_mlx *mlx, t_img *img, t_data *data)
{
	int i;
	int j;
	t_color col;
	int t;
	int col_i[3];

	ft_camera_viewport(mlx, data);
	j = 0.0;
	while (j < mlx->y_res)
	{
		i = 0.0;
		while (i < mlx->x_res)
		{
			col = get_color(0, 0, 0);
			data->ray = get_ray(data, mlx, i, j);
			col = scene_trace(data);
			col_i[0] = (int)(255.00 * col.r);
			col_i[1] = (int)(255.00 * col.g);
			col_i[2] = (int)(255.00 * col.b);
			t = j * mlx->x_res + i;
			img->addr[t] = ((col_i[0] << 16) | (col_i[1] << 8) | (col_i[2] << 0));
			i++;
		}
		j++;
	}
}

int key_press(int button, t_mlx *mlx)
{
	mlx->k = 0;
	if (button == ESC)
		exit(0);
	printf("key_code ==> %d\n", button);
	return (0);
}

int main(int ac, char **av)
{
	t_mlx mlx;
	t_img img;
	t_data data;

	if (ac != 2)
	{
		printf("error\n");
		exit(0);
	}
	ft_pars_scene(&data, &mlx, av);

	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, mlx.x_res, mlx.y_res, "MiniRT");
	img.img = mlx_new_image(mlx.mlx_ptr, mlx.x_res, mlx.y_res);
	img.addr = (int *)mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.size_line, &img.endian);
	trace_ray(&mlx, &img, &data);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, img.img, 0, 0);
	mlx_hook(mlx.win_ptr, 2, 0, key_press, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
