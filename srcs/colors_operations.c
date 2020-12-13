/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 12:29:18 by asaadi            #+#    #+#             */
/*   Updated: 2020/12/02 17:10:30 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color		get_color(double r, double g, double b)
{
	t_color col;

	col.r = r;
	col.g = g;
	col.b = b;
	return (col);
}

void		min_max_color(t_color *result)
{
	result->r = (result->r > 1.0) ? 1.0 : result->r;
	result->g = (result->g > 1.0) ? 1.0 : result->g;
	result->b = (result->b > 1.0) ? 1.0 : result->b;
	result->r = (result->r < 0.0) ? 0.0 : result->r;
	result->g = (result->g < 0.0) ? 0.0 : result->g;
	result->b = (result->b < 0.0) ? 0.0 : result->b;
}

t_coord		point_of_hit(double t, t_ray r)
{
	t_coord point;

	point.x = r.origin.x + t * r.direction.x;
	point.y = r.origin.y + t * r.direction.y;
	point.z = r.origin.z + t * r.direction.z;
	return (point);
}

t_color		add_color(t_color col1, t_color col2)
{
	t_color ret_col;

	ret_col.r = col1.r + col2.r;
	ret_col.g = col1.g + col2.g;
	ret_col.b = col1.b + col2.b;
	return (ret_col);
}

t_color		sca_mult_col(t_color col, double k)
{
	t_color ret_col;

	ret_col.r = col.r * k;
	ret_col.g = col.g * k;
	ret_col.b = col.b * k;
	return (ret_col);
}
