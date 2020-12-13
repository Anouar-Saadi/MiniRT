/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_image_bmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 09:55:19 by asaadi            #+#    #+#             */
/*   Updated: 2020/12/04 09:10:49 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_file_header	create_file_header(t_data *data)
{
	t_file_header file_header;

	file_header.file_type[0] = 'B';
	file_header.file_type[1] = 'M';
	file_header.reversed = 0;
	file_header.file_size = 14 + 40 +
	(unsigned int)(data->mlx.x_res * data->mlx.y_res * 4);
	file_header.offset_bits = 54;
	return (file_header);
}

t_infos_header	create_info_header(t_data *data)
{
	t_infos_header bit_info;

	bit_info.header_size = 40;
	bit_info.img_width = data->mlx.x_res;
	bit_info.img_height = data->mlx.y_res;
	bit_info.planes = 1;
	bit_info.bits_per_pixel = 32;
	bit_info.compression = 0;
	bit_info.image_size = data->mlx.x_res * data->mlx.y_res * 4;
	bit_info.x_pixel_per_meter = 0;
	bit_info.y_pixel_per_meter = 0;
	bit_info.colors = 0;
	bit_info.important_colors = 0;
	return (bit_info);
}

static void		copy_data(t_data *data, int *fd)
{
	int i;

	i = data->mlx.x_res * data->mlx.y_res;
	while (i > 0)
	{
		write(*fd, &data->img.addr[i], 4);
		i--;
	}
}

void			get_pixel_data(t_data *data, int *fd)
{
	int i;
	int size_line;
	int save;
	int p;

	i = 0;
	data->img.size_line /= 4;
	while (i < data->mlx.y_res)
	{
		p = 0;
		size_line = data->img.size_line;
		while (p < size_line && p != size_line)
		{
			save = data->img.addr[p + (i * data->img.size_line)];
			data->img.addr[p + (i * data->img.size_line)] =
			data->img.addr[size_line + (i * data->img.size_line - 1)];
			data->img.addr[size_line + (i * data->img.size_line - 1)] = save;
			p++;
			size_line--;
		}
		i++;
	}
	copy_data(data, fd);
}

void			ft_create_image_bmp(t_data *data)
{
	t_file_header	file_header;
	t_infos_header	info_header;
	unsigned char	header[54];
	int				fd;

	fd = open("miniRT.bmp", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd < 0)
		ft_put_error(data, "Error at creating image bmp");
	file_header = create_file_header(data);
	info_header = create_info_header(data);
	ft_memset(header, 0, 54);
	ft_memcpy(header, "BM", 2);
	ft_memcpy(header + 2, (char*)&(file_header.file_size), 4);
	ft_memcpy(header + 10, (char*)&(file_header.offset_bits), 4);
	ft_memcpy(header + 14, (char*)&(info_header.header_size), 4);
	ft_memcpy(header + 18, (char*)&(info_header.img_width), 4);
	ft_memcpy(header + 22, (char*)&(info_header.img_height), 4);
	ft_memcpy(header + 26, (char*)&(info_header.planes), 2);
	ft_memcpy(header + 28, (char*)&(info_header.bits_per_pixel), 2);
	ft_memcpy(header + 34, (char*)&(info_header.image_size), 4);
	write(fd, &header, 54);
	get_pixel_data(data, &fd);
	close(fd);
}
