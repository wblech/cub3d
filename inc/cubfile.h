/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubfile.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 11:53:28 by wbertoni          #+#    #+#             */
/*   Updated: 2021/04/02 19:15:44 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBFILE_H
# define CUBFILE_H

# include <stdio.h>
# include <unistd.h>
# include "get_next_line.h"
# include "../libft/libft.h"

# define TRUE 1
# define FALSE 0

# ifndef TILE_SIZE
#  define TILE_SIZE 64
# endif

typedef struct	s_map
{
	char		**map;
	int			num_row;
	int			num_col;
	char		initial_pl_cardinal;
	int			initial_pl_x;
	int			initial_pl_y;
	int			num_sprite;
}				t_map;

typedef struct	s_file
{
	int			width;
	int			height;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		*sprite;
	int			floor;
	int			ceiling;
	t_map		*map;
}				t_file;

typedef enum	e_face
{
	up,
	down,
	left,
	right
}				t_face;

typedef enum	e_error_file
{
	noerror,
	eallow,
	enull,
	ewall,
	eempty,
	erespos,
	eresarg,
	epathtex,
	ecolortex,
	ergbsize,
	enores,
	enotexture,
	enocolor,
	enomap,
	eplayer,
	espace,
	erepeat,
	epldoubled,
	novalidkey
}				t_error_file;

int g_resolution;
int g_ceiling;
int g_floor;

void			ft_print_error_cubfile(t_error_file error);
char			**ft_malloc_map(int row, int col);
int				ft_is_w_or_s(int c);
t_file			*ft_cubfile(char *cubfile);
int				ft_check_map_cubfile_has_empty_line(char **line);
t_error_file	ft_check_map_cubfile(t_map *map);
t_error_file	ft_get_map_cubfile(t_file *file, char *line);
t_error_file	ft_get_info_value(t_file *file, char **info);
t_file			*ft_cubfile(char *cubfile);
int				ft_cubfile_check_and_get_function(t_file *file);
t_error_file	ft_get_cubfile_value(t_file *file, char *line);
t_error_file	ft_malloc_file_map(t_file *file);
void			ft_del_file(t_file *file);
void			ft_del_map(t_map *map);
void			ft_del_info(char **info);
void			ft_putstr(char *str);
t_error_file	ft_check_cubfile(t_file *file);
t_error_file	ft_get_texture_path_norminette(t_file *file, char **info);
t_error_file	ft_is_player_doubled(t_file *file);
int				ft_check_ceiling_floor(char **rgb);
void			ft_set_player_position(t_file *file, int i, int j);
int				ft_get_size(char **str);
int				ft_check_diagonal_map_surronded(t_map *map);
int				ft_is_repeated_flag(char **info);

#endif
