/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 10:23:01 by asaadi            #+#    #+#             */
/*   Updated: 2020/12/04 13:13:54 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_calcul_vec(t_camera *camera)
{
	camera->w = camera->look_at;
	camera->w = vect_scal(-1, camera->look_at);
	camera->w = unit_vector(camera->w);
	camera->u = vec_cross(&camera->v_up, &camera->w);
	camera->u = unit_vector(camera->u);
	camera->v = vec_cross(&camera->w, &camera->u);
}

void	ft_camera_viewport(t_data *data, t_camera *camera)
{
	double	aspect_ratio;
	double	tetha;
	t_coord	tmp;

	camera->v_up = new_vector(0, 1, 0);
	if ((camera->look_at.y > 0 || camera->look_at.y < 0) &&
			(camera->look_at.x == 0 && camera->look_at.z == 0))
		camera->v_up = new_vector(0, 0, -1);
	tetha = camera->fov * M_PI / 180;
	aspect_ratio = data->mlx.x_res / data->mlx.y_res;
	data->mlx.viewport_height = 2.0 * tan(-tetha / 2);
	data->mlx.viewport_width = aspect_ratio * data->mlx.viewport_height;
	ft_calcul_vec(camera);
	data->ray.origin = camera->eye;
	camera->centre = sub_vec(&camera->eye, &camera->w);
	tmp = vect_scal(data->mlx.viewport_width / 2, camera->u);
	camera->lower_left_corner = sub_vec(&camera->centre, &tmp);
	tmp = vect_scal(data->mlx.viewport_height / 2.0, camera->v);
	camera->lower_left_corner = sub_vec(&camera->lower_left_corner,
										&tmp);
}

t_ray	get_ray(t_data *data, t_camera *camera, int i, int j)
{
	t_coord pixel_pos;
	t_coord tmp;

	tmp = vect_scal((i + 0.5) * data->mlx.viewport_width / data->mlx.x_res,
					camera->u);
	pixel_pos = vec_add(&camera->lower_left_corner, &tmp);
	tmp = vect_scal((j + 0.5) * data->mlx.viewport_height / data->mlx.y_res,
					camera->v);
	pixel_pos = vec_add(&pixel_pos, &tmp);
	data->ray.direction = sub_vec(&pixel_pos, &data->ray.origin);
	data->ray.direction = unit_vector(data->ray.direction);
	return (data->ray);
}
