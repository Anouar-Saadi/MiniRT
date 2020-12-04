/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 10:23:01 by asaadi            #+#    #+#             */
/*   Updated: 2020/11/16 17:46:16 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void ft_calcul_vec(t_data *data)
{
	data->camera->w = sub_vec(&data->camera->eye, &data->camera->look_at);
	data->camera->w = unit_vector(data->camera->w);
	data->camera->u = vec_cross(&data->camera->v_up, &data->camera->w);
	data->camera->u = unit_vector(data->camera->u);
	data->camera->v = vec_cross(&data->camera->w, &data->camera->u);
}

void ft_camera_viewport(t_mlx *mlx, t_data *data)
{
	double aspect_ratio;
	double tetha;
	t_coord tmp;

	data->camera->v_up.x = 0.0;
	data->camera->v_up.y = 1.0;
	data->camera->v_up.z = 0.0;
	tetha = data->camera->fov * M_PI / 180;
	aspect_ratio = mlx->x_res / mlx->y_res;
	mlx->viewport_height = 2.0 * tan(tetha / 2);
	mlx->viewport_width = aspect_ratio * mlx->viewport_height;
	ft_calcul_vec(data);
	data->ray.origin = data->camera->eye;
	data->camera->centre = sub_vec(&data->camera->eye, &data->camera->w);
	tmp = vect_scal(mlx->viewport_width / 2, data->camera->u);
	data->camera->lower_left_corner = sub_vec(&data->camera->centre, &tmp);
	tmp = vect_scal(mlx->viewport_height / 2.0, data->camera->v);
	data->camera->lower_left_corner = sub_vec(&data->camera->lower_left_corner,
											  &tmp);
}

t_ray get_ray(t_data *data, t_mlx *mlx, int i, int j)
{
	t_coord pixel_pos;
	t_coord tmp;

	tmp = vect_scal((i + 0.5) * mlx->viewport_width / mlx->x_res,
					data->camera->u);
	pixel_pos = vec_add(&data->camera->lower_left_corner, &tmp);
	tmp = vect_scal((j + 0.5) * mlx->viewport_height / mlx->y_res,
					data->camera->v);
	pixel_pos = vec_add(&pixel_pos, &tmp);
	data->ray.direction = sub_vec(&pixel_pos, &data->ray.origin);
	data->ray.direction = unit_vector(data->ray.direction);
	return (data->ray);
}
