/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:10:11 by asaadi            #+#    #+#             */
/*   Updated: 2020/12/04 10:23:53 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		ft_close(t_data *data)
{
	ft_free_data_scene(data);
	exit(0);
}

void	ft_init_data(t_data *data)
{
	data->mlx.x_res = 0;
	data->mlx.y_res = 0;
	data->illum.ka = -1;
	data->camera = NULL;
	data->light = NULL;
	data->objects = NULL;
	data = NULL;
}

int		main(int ac, char **av)
{
	t_data data;

	if (ac > 1 && ac < 4)
	{
		ft_bzero(&data, sizeof(t_data));
		ft_init_data(&data);
		ft_pars_scene(&data, av);
		if (ac == 2)
			ft_create_the_window(&data, av[1]);
		if (ac == 3 && (strncmp(av[2], "--save", 6) == 0
					|| strncmp(av[2], "-save", 5) == 0))
			ft_create_image(&data);
		else
			ft_put_error(&data, "the second arguments must be --save");
	}
	else
		ft_put_error(&data, "There's somthing wrong in arguments.");
	return (0);
}
