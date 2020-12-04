/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 10:11:59 by asaadi            #+#    #+#             */
/*   Updated: 2020/11/06 20:12:23 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double ft_long(double res, double sign)
{
	if (res == 0.0 && sign < 0.0)
		return (-1.0);
	if (res < 0.0 && sign > 0.0)
		return (-1.0);
	if (res > 0.0 && sign < 0.0)
		return (0.0);
	return (res);
}

double ft_strtod(const char *str)
{
	double res;
	double res1;
	double sign;
	int i;
	int j;

	if (!*str)
		return (0.0);
	res = 0.0;
	res1 = 0.0;
	sign = 1.0;
	i = 0;
	while ((str[i] == '\t' || str[i] == '\n' || str[i] == '\v' ||
			str[i] == '\f' || str[i] == '\r' || str[i] == ' ') &&
		   str[i])
		i++;
	if ((str[i] == '-' || str[i] == '+') && str[i])
	{
		if (str[i] == '-')
			sign *= -1.0;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			res = sign * res;
			return (ft_long(res, sign));
		}
		j = 0;
		while ((str[i] >= '0' && str[i] <= '9') && str[i])
		{
			res1 = res1 * 10 + (str[i] - '0');
			i++;
			j++;
		}
		res = res + (res1 / pow(10, j));
	}
	if (res != 0.0)
		res = sign * res;
	return (ft_long(res, sign));
}