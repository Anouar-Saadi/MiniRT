/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 15:42:54 by asaadi            #+#    #+#             */
/*   Updated: 2020/11/19 17:57:35 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coord	new_vector(double x, double y, double z)
{
	t_coord new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_coord	sub_vec(t_coord *v1, t_coord *v2)
{
	t_coord result;

	result.x = v1->x - v2->x;
	result.y = v1->y - v2->y;
	result.z = v1->z - v2->z;
	return (result);
}

double	vec_dot(t_coord v1, t_coord v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

t_coord	vect_scal(double sca, t_coord vec)
{
	t_coord result;

	result.x = vec.x * sca;
	result.y = vec.y * sca;
	result.z = vec.z * sca;
	return (result);
}

t_coord	vec_add(t_coord *v1, t_coord *v2)
{
	t_coord result;

	result.x = v1->x + v2->x;
	result.y = v1->y + v2->y;
	result.z = v1->z + v2->z;
	return (result);
}
