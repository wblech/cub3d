/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 19:26:09 by wbertoni          #+#    #+#             */
/*   Updated: 2020/11/02 13:52:40 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_CUB3D_H
# define CUB3D_CUB3D_H

# include "cubfile.h"
# include "struct_cub3d.h"
# include "math.h"

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

# define PI 3.14159265
# define TWO_PI 6.28318530
# define FOV_ANGLE (60 * (PI / 180))

# define NORTH 3 * (PI / 2)
# define SOUTH PI / 2
# define WEST PI
# define EAST 0
# define KEY_W 0x0077
# define KEY_S 0x0073
# define KEY_A 0x0061
# define KEY_D 0x0064
# define KEY_ESC 0xff1b
# define KEY_M 0x006d
# define ARROW_LEFT 0xff51
# define ARROW_RIGHT 0xff53
# define MINIMAP_SCALE_FACTOR 1.0

void my_mlx_pixel_put(t_img *img, int x, int y, int color);
t_point ft_create_point(float x, float y, int color);
void ft_rect_filled_borderless(t_img *img, t_point start, t_point size);
void ft_circle_filled(t_img *img, t_point center, int r);
void ft_line_dda(t_img *img, t_point start, t_point end);


#endif
