/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_operations_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:08:11 by asaadi            #+#    #+#             */
/*   Updated: 2020/12/02 17:11:06 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color		sca_div_col(t_color col, double k)
{
	t_color ret_col;

	ret_col.r = col.r / k;
	ret_col.g = col.g / k;
	ret_col.b = col.b / k;
	return (ret_col);
}

t_color		multiply_col(t_color col1, t_color col2)
{
	t_color ret_col;

	ret_col.r = col1.r * col2.r;
	ret_col.g = col1.g * col2.g;
	ret_col.b = col1.b * col2.b;
	return (ret_col);
}
