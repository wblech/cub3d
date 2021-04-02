/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_bmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 15:54:39 by wbertoni          #+#    #+#             */
/*   Updated: 2021/04/02 13:24:02 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	little_endian_int(unsigned char *addr, unsigned int value)
{
	addr[0] = (unsigned char)(value);
	addr[1] = (unsigned char)(value >> 8);
	addr[2] = (unsigned char)(value >> 16);
	addr[3] = (unsigned char)(value >> 24);
}

static int	store_color(t_game *game, int x, int y)
{
	unsigned int	color;
	unsigned char	addr_color[4];

	color = *(unsigned int *)(game->frame->addr +
	game->cubfile->width * (game->cubfile->height - y - 1) * 4 +
	x * 4);
	little_endian_int(&addr_color[0], color);
	return (*(unsigned int*)(addr_color));
}

static void	bmp_header(t_game *game, int fd)
{
	unsigned char	file[54];
	int				filesize;

	ft_bzero(&file, 54);
	filesize = 54 + game->cubfile->height * game->cubfile->width
	* game->frame->bits_per_pixel / 8;
	file[0] = (unsigned char)('B');
	file[1] = (unsigned char)('M');
	little_endian_int(&file[2], filesize);
	file[10] = (unsigned char)(54);
	file[14] = (unsigned char)(40);
	little_endian_int(&file[18], game->cubfile->width);
	little_endian_int(&file[22], game->cubfile->height);
	file[26] = (unsigned char)(1);
	file[28] = (unsigned char)(32);
	write(fd, &file, 54);
}

int			save_bmp_file(t_game *game)
{
	int		fd;
	int		bmp[game->cubfile->height][game->cubfile->width];
	int		x;
	int		y;

	if ((fd = open("im.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 444)) < 0)
		return (0);
	bmp_header(game, fd);
	y = 0;
	while (y < game->cubfile->height)
	{
		x = 0;
		while (x < game->cubfile->width)
		{
			bmp[y][x] = store_color(game, x, y);
			write(fd, &bmp[y][x], 4);
			x++;
		}
		y++;
	}
	close(fd);
	return (1);
}
