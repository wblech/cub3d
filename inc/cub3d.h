/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 19:26:09 by wbertoni          #+#    #+#             */
/*   Updated: 2021/04/02 11:55:50 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
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
# define FOV_ANGLE 60

# define WALL_STRIP_WIDTH 1

# define NORTH 4.71
# define SOUTH 1.57
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
# define MINIMAP_SCALE_FACTOR 0.1

int g_minimap;

void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
t_point		ft_create_point(float x, float y, int color);
void		ft_rect_filled_borderless(t_img *img, t_point start, t_point size);
void		ft_circle_filled(t_img *img, t_point center, int r);
void		ft_line_dda(t_img *img, t_point start, t_point end);

/*
** player.c
*/
int			ft_get_player_position(t_game *game);
int			new_position_player(int keycode, t_game *game);

/*
** helpers.c
*/
int			ft_is_pointer_null(void *ptr);
int			ft_get_error(int (*func)(void *), void *a, char *msg);
float		ft_distance_between_points(t_point start, t_point end);
int			ft_calc_facing(float ray_angle, t_face face);
void		ft_sort_sprites(int num_visible_sprites, t_sprite *visible_sprites);

/*
** ft_helper_angle.c
*/
float		ft_degtorad(float degree);
float		ft_normalize_angle(float angle);

/*
** ft_collision.c
*/
int			is_end_window(t_game *game, float x, float y);
int			ft_has_wall(t_game *game, float x, float y, char id);

/*
** main.c
*/
int			ft_render(t_game *game);
void		ft_del_rays(t_game *game);

/*
** ft_draw_2d_map.c
*/
int			ft_draw_2d_map(t_game *game, t_img *img);

/*
** ft_ray_cast.c
*/
int			ft_raycast(t_game *game);

/*
** ft_helper_raycasting.c
*/
float		get_x_to_check(float next_x, float ray_angle, int is_vert);
float		get_y_to_check(float next_y, float ray_angle, int is_vert);
void		ft_helper_rc(t_game *game, t_ray **rays);

/*
** ft_get_alltextures.c
*/
int			ft_get_all_textures(t_game *game);

/*
** ft_texture.c
*/
t_tex		*ft_create_texture(void *mlx_ptr, char *path);
int			ft_texture_byte(t_tex *texture, t_point pos);
int			ft_get_texture_color(t_game *game, float wall_height, int index,
						int y);

/*
** ft_draw_3d_map.c
*/
void		ft_draw_3d_map(t_game *game, t_img *img);

/*
** ft_update_release_key.c
*/
int			ft_update_press(int keycode, t_game *game);
int			ft_update_release(int keycode, t_game *game);

/*
** ft_close.c
*/
int			ft_close(t_game *game);
void		ft_del_texture_orchestrator(t_game *game);

/*
** ft_2d_helper.c
*/
void		ft_change_minimap_status(void);

/*
** ft_create_destroy_img.c
*/
t_img		*ft_create_img(t_game *game);
void		ft_destroy_free_set_img(t_game *game, t_img *new_img);

/*
** ft_sprite_1.c
*/
void		ft_render_map_sprites(t_game *game, t_img *img);
void		ft_get_sprite_pos(t_game *game, int x, int y, int count);
void		ft_get_all_sprites_pos(t_game *game);
void		ft_render_map_sprites(t_game *game, t_img *img);
t_sprite	ft_set_visible_sprites(t_game *game, int i,
float angle_sprite_player);
float		ft_get_angle_sprite_player(t_game *game, int i);
int			ft_get_visible_sprites(t_game *game, t_sprite *visible_sprites);

/*
** ft_sprite_2.c
*/
void		ft_draw_sprite_3d(t_game *game, t_img *img, t_sprite sprite);
void		ft_render_sprite_projection(t_game *game, t_img *img);

/*
** ft_save_bmp.c
*/
int			save_bmp_file(t_game *game);

/*
** ft_check_args.c
*/
int			check_args(int argc, char **argv);

/*
** ft_check_resolution.c
*/
void		ft_check_resolution(t_game *game);

/*
** ft_create_ray_once.c
*/
int			ft_create_ray_once(t_game *game);

/*
** ft_setup_norminette.c
*/
int			ft_setup_norminette(t_game *game, char * path);

#endif
