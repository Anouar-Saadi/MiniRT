/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 10:11:59 by asaadi            #+#    #+#             */
/*   Updated: 2020/12/02 17:07:33 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	ft_long(double res, double sign)
{
	if (res == 0.0 && sign < 0.0)
		return (-1.0);
	if (res < 0.0 && sign > 0.0)
		return (-1.0);
	if (res > 0.0 && sign < 0.0)
		return (0.0);
	return (res);
}

static double	check_after_point(const char *str, double result,
		double sign, int here)
{
	int		i;
	int		j;
	double	res1;
	double	res;

	i = here;
	res = result;
	res1 = 0;
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
	return (res);
}

static int		ft_whitespaces(const char *str, int j)
{
	int i;

	i = j;
	while ((str[i] == '\t' || str[i] == '\n' || str[i] == '\v' ||
		str[i] == '\f' || str[i] == '\r' || str[i] == ' ') &&
			str[i])
		i++;
	return (i);
}

double			ft_strtod(const char *str)
{
	double	res;
	double	sign;
	int		i;

	if (!*str)
		return (0.0);
	res = 0;
	sign = 1.0;
	i = 0;
	i = ft_whitespaces(str, i);
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
		res = check_after_point(str, res, sign, i);
	res = (res != 0.0) ? sign * res : 0;
	return (ft_long(res, sign));
}
