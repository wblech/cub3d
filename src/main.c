/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 12:40:19 by wbertoni          #+#    #+#             */
/*   Updated: 2020/06/03 16:32:22 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int g_count = 0;

t_map *ft_fake_map()
{
	t_map *map_clone;
	int i_row;
	int i_col;
	// int map[11][15] = {
	// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	// 	{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
	char map[11][15] = {
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
		{'1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}};
	i_row = 0;
	i_col = 0;
	map_clone = malloc(sizeof(t_map));
	map_clone->num_col = 15;
	map_clone->num_row = 11;
	map_clone->map = malloc(map_clone->num_row * sizeof(char *));

	while (i_row < map_clone->num_row)
	{
		map_clone->map[i_row] = (char *)malloc(map_clone->num_col * sizeof(char));
		while (i_col < map_clone->num_col)
		{
			map_clone->map[i_row][i_col] = map[i_row][i_col];
			i_col++;
		}
		i_col = 0;
		i_row++;
	}
	return (map_clone);
}

void ft_del_info(char **info)
{
	int i;

	i = 0;
	while (info[i] != '\0')
	{
		free(info[i]);
		i++;
	}
	free(info);
}

int	ft_get_ceiling_floor_color(t_file *file, char **info)
{
	char **rgb;
	int size;

	size = 0;
	while (info[size] != '\0')
		size++;
	if (size < 2)
	{
		printf("Error:\nNeed to inform a color to the texture\n");
		return (0);
	}
	rgb = ft_split(info[1], ',');
	if (ft_strncmp("F", info[0], 3) == 0)
		file->floor = ft_atoi(rgb[0]) << 16 | ft_atoi(rgb[1]) << 8
		| ft_atoi(rgb[2]);
	else if (ft_strncmp("C", info[0], 3) == 0)
		file->ceiling = ft_atoi(rgb[0]) << 16 | ft_atoi(rgb[1]) << 8
		| ft_atoi(rgb[2]);
	ft_del_info(rgb);
	return (1);
}

int ft_get_texture_path(t_vars *vars, t_file *file, char **info)
{
	int size;

	size = 0;
	while (info[size] != '\0')
		size++;
	if (size < 2)
	{
		printf("Error:\nNeed to inform path to the texture\n");
		return (0);
	}
	if ((ft_strncmp("NO", info[0], 3) == 0))
		file->north = ft_create_texture(vars->mlx, info[1]);
	else if ((ft_strncmp("SO", info[0], 3) == 0))
		file->south = ft_create_texture(vars->mlx, info[1]);
	else if ((ft_strncmp("WE", info[0], 3) == 0))
		file->west = ft_create_texture(vars->mlx, info[1]);
	else if ((ft_strncmp("EA", info[0], 3) == 0))
		file->east = ft_create_texture(vars->mlx, info[1]);
	else if ((ft_strncmp("S", info[0], 3) == 0))
		file->sprite = ft_create_texture(vars->mlx, info[1]);
	printf("depois\n");
	return (1);
}

int ft_get_resolution(t_file *file, char **info)
{
	int size;

	size = 0;
	while (info[size] != '\0')
		size++;
	if (size < 3)
	{
		printf("Error:\nNeed 2 arguments for resolution in cub file\n");
		return (0);
	}
	if (!ft_isdigit(info[1][0]) || !ft_isdigit(info[2][0]))
	{
		printf("Error:\nResolution width and height must be positive numbers\n");
		return (0);
	}
	file->width = ft_atoi(info[1]);
	file->height = ft_atoi(info[2]);
	ft_del_info(info);
	return (1);
}

void ft_cub_value(t_vars *vars, t_file *file, char *line)
{
	int i;
	char **info;
	// t_map *map;

	i = 0;

	// while (ft_isspace(line[i]))
	// 	i++;
	// if (ft_isdigit(line[i]))
	// 	ft_get_map(file, line, map);
	info = ft_split(line, ' ');
	if (ft_strncmp("R", info[0], 3) == 0)
		ft_get_resolution(file, info);
	else if ((ft_strncmp("NO", info[0], 3) == 0)
	|| (ft_strncmp("SO", info[0], 3) == 0)
	|| (ft_strncmp("WE", info[0], 3) == 0)
	|| (ft_strncmp("EA", info[0], 3) == 0)
	|| (ft_strncmp("S", info[0], 3) == 0))
		ft_get_texture_path(vars, file, info);
	else if ((ft_strncmp("F", info[0], 3) == 0)
	|| (ft_strncmp("C", info[0], 3) == 0))
		ft_get_ceiling_floor_color(file, info);
}
// se espaço lê o próximo até fim da linha;
// se R pega 2 números separados por espaço(função libft)
// se NO, SO, WE, EA, S salva path na struct
// Se F ou C transforma em int e salva
// Se 0/2/N/S/W/E erro dizendo que não começou com 1
// Senão inica leitura de mapa,se tiver linha vazia para.
// map[i] - pega tamanho da linha

// int ft_check_map()

void *ft_spacelloc(size_t count, size_t size)
{
	char *ptr;

	ptr = ft_calloc(count, size);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, ' ', count * size);
	return (ptr);
}

void **ft_malloc_map(int row, int col)
{
	char **ptr;
	int i;

	i = 0;
	ptr = (char *)malloc(row * sizeof(char *));
	while (i < row)
	{
		ptr[i] = (char *)ft_spacelloc(col + 1, sizeof(char));
		i++;
	}
	return (ptr);
}

void ft_del_map(char **map, int num_row)
{
	int i;

	i = 0;
	while (i < num_row)
	{
		free(map[i]);
		i++;
	}
}

int ft_get_map(t_file *file, char *line)
{
	int size;
	int i;
	int j;
	char **tmp;

	j = 0;
	i = 0;
	size = ft_strlen(line);
	if (file->map->num_row == 0)
	{
		file->map->num_row++;
		file->map->num_col = size;
		file->map->map = ft_malloc_map(file->map->num_row, file->map->num_col);
		while(j < size)
		{
			file->map->map[0][j] = line[j];
			j++;
		}
	} else
	{
		tmp = file->map->map;
		file->map->num_row++;

		if (size > file->map->num_col)
			file->map->num_col = size;

		file->map->map = ft_malloc_map(file->map->num_row, file->map->num_col);

		while (i < file->map->num_row)
		{
			while (j < file->map->num_col)
			{
				if (tmp[i][j] != '\0')
					file->map->map[i][j] = tmp[i][j];
				else
					break;
			j++;
			}
			j = 0;
			i++;
		}
		ft_del_map(file->map->map, file->map->num_row);

	}
}

t_file *ft_read_cubfile(t_vars *vars, char *cubfile)
{
	int fopen;
	char **line;
	int ret;
	t_file *file;

	file = (t_file *)malloc(sizeof(t_file));
	line = (char **)malloc(sizeof(char));
	file->map = (t_map *)malloc(sizeof(t_map));
	file->map->num_col = 0;
	file->map->num_row = 0;
	fopen = open(cubfile, O_RDONLY);
	while ((ret = get_next_line(fopen, line)))
	{
		printf("%s\n", *line);
		ft_cub_value(vars, file, *line);
	}
	// printf("width: %i\n", file->width);
	// printf("height: %i\n", file->height);
	// printf("North: %s\n", file->north);
	// printf("South: %s\n", file->south);
	// printf("West: %s\n", file->west);
	// printf("East: %s\n", file->east);
	// printf("Sprite: %s\n", file->sprite);
	// printf("Ceiling: %x\n", file->ceiling);
	// printf("Floor: %x\n", file->floor);
	free(*line);
	free(line);
	return (file);
}

int ft_setup(t_vars *vars, char *path)
{
	t_map *map;

	g_minimap = TRUE;
	map = ft_fake_map();
	if (!ft_create_vars(vars, map, path))
		return (0);
	if (!ft_raycast(vars))
		return (0);
	ft_draw_2d_map(vars, vars->img);
	ft_draw_3d_map(vars, vars->img);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (1);
}

int main(int argc, char **argv)
{
	t_vars vars;
	t_map *map;

	// if (argc < 2)
	// {
	// 	printf("Error:\nMap file not found");
	// 	return(1);
	// }
	(void)argc;
	map = ft_fake_map();
	if (!ft_setup(&vars, argv[1]))
		exit(1);
	if (!mlx_hook(vars.win, 2, 1L << 0, ft_update_press, &vars))
		exit(1);
	if (!mlx_hook(vars.win, 3, 1L << 1, ft_update_release, &vars))
		exit(1);
	if (!mlx_hook(vars.win, 17, 1L << 17, ft_close, &vars))
		exit(1);
	if (!mlx_expose_hook(vars.win, ft_render, &vars))
		exit(1);
	mlx_loop(vars.mlx);
	return (0);
}
