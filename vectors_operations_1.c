/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_operations_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 12:25:55 by asaadi            #+#    #+#             */
/*   Updated: 2020/11/19 18:03:48 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coord	vec_div(t_coord *v1, t_coord *v2)
{
	t_coord result;

	result.x = v1->x / v2->x;
	result.y = v1->y / v2->y;
	result.z = v1->z / v2->z;
	return (result);
}

t_coord	vec_div_sca(t_coord v1, double sca)
{
	t_coord result;

	result.x = v1.x / sca;
	result.y = v1.y / sca;
	result.z = v1.z / sca;
	return (result);
}

t_coord	vec_cross(t_coord *v1, t_coord *v2)
{
	t_coord	result;

	result.x = v1->y * v2->z - v1->z * v2->y;
	result.y = v1->x * v2->z - v1->z * v2->x;
	result.z = v1->x * v2->y - v1->y * v2->x;
	return (result);
}

double	lenght(t_coord vec)
{
	return (sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z)));
}

t_coord	unit_vector(t_coord v)
{
	t_coord result;

	result = vec_div_sca(v, lenght(v));
	return (result);
}
