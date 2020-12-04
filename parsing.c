/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 08:59:36 by asaadi            #+#    #+#             */
/*   Updated: 2020/11/18 11:44:57 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void ft_pars_scene(t_data *data, t_mlx *mlx, char **av)
{
    int fd;
    int read;
    char *line;
    // t_data *tmp = data;

    line = NULL;
    fd = open(av[1], O_RDONLY, S_IRUSR | S_IWUSR | S_IXUSR);
    while ((read = get_next_line(fd, &line)) > 0)
    {
        if (line[0] == 'R')
            parser_resolution(mlx, line);
        else if (line[0] == 'A')
            parser_ambiant_light(data, line);
        else if (line[0] == 'c' && line[1] == ' ')
            parser_camera(data, line);
        else if (line[0] == 'l' && line[1] == ' ')
            parser_light(data, line);
        else if (line[0] == 'p' && line[1] == 'l')
        {
            parser_plane(data, line);
        }
        else if (line[0] == 's' && line[1] == 'p')
        {
            parser_sphere(data, line);
        }
        else if (line[0] == 's' && line[1] == 'q')
            parser_square(data, line);
        else if (line[0] == 'c' && line[1] == 'y')
            parser_cylinder(data, line);
        else if (line[0] == 't' && line[1] == 'r')
            parser_triangle(data, line);
        free(line);
    }
    // while (tmp->light)
    // {
    // printf("\n |%f| \n\n", tmp->light->kd);
    // printf("\n++++++++\n\n");
    // tmp->light = tmp->light->next;
    // }
    free(line);
    close(fd);
}