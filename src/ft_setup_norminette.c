/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup_norminette.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 11:54:20 by wbertoni          #+#    #+#             */
/*   Updated: 2021/04/02 11:58:20 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_setup_norminette(t_game *game, char *path)
{
	game->cubfile = ft_cubfile(path);
	if (ft_get_error(&ft_is_pointer_null, game->cubfile, "Error:\nCouldn´t \
get cubfile info"))
	{
		free(game);
		return (FALSE);
	}
	if (!ft_initialize_window(game) || !ft_get_player_position(game))
		return (FALSE);
	if (!ft_get_all_textures(game))
		return (FALSE);
	return (TRUE);
}
