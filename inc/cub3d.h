/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 19:26:09 by wbertoni          #+#    #+#             */
/*   Updated: 2020/10/24 18:48:16 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_CUB3D_H
# define CUB3D_CUB3D_H

# include "cubfile.h"
# include "struct_cub3d.h"

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

void my_mlx_pixel_put(t_img *img, int x, int y, int color);

#endif
