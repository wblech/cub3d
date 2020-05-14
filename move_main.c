#include "cub3d.h"

// int		ft_show(int keycode, t_vars *vars)
// {
// 	(void)vars;
// 	printf("%x\n", keycode);
// 	return (0);
// }

t_data *create_image(void *mlx_ptr, int x, int y)
{
	t_data *img;

	img = malloc(1 * sizeof(t_data));
	if (!img)
		return (NULL);
	img->img = mlx_new_image(mlx_ptr, x, y);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	return (img);
}

void ft_destroy_free_set_img(t_vars *vars, t_data *new_img)
{
	mlx_destroy_image(vars->mlx, vars->img->img);
	free(vars->img);
	vars->img = new_img;
}

int ft_move(int keycode, t_vars *vars)
{
	t_data *new_img;

	new_img = create_image(vars->mlx, 600, 480);
	if (!new_img)
		return (NULL);
	if (keycode == KEY_W)
		vars->pos->y -= 1;
	if (keycode == KEY_S)
		vars->pos->y += 1;
	if (keycode == KEY_A)
		vars->pos->x -= 1;
	if (keycode == KEY_D)
		vars->pos->x += 1;
	ft_circle_filled(new_img, *vars->pos, 100);
	mlx_put_image_to_window(vars->mlx, vars->win, new_img->img, 0, 0);
	ft_destroy_free_set_img(vars, new_img);
	return (0);
}

int setup(t_vars *vars)
{
	vars->img = create_image(vars->mlx, 600, 480);
	ft_circle_filled(vars->img, *vars->pos, 100);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0);
}

int main(void)
{
	t_vars vars;
	t_point center;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 600, 480, "Movement");

	center = ft_create_point(400, 300, 0x00ff0000);
	vars.pos = &center;

	setup(&vars);
	//update()
	//render()
	// mlx_key_hook(vars.win, ft_move, &vars);
	mlx_hook(vars.win, 2, 1L << 0, ft_move, &vars);
	// mlx_key_hook(vars.win, ft_move, &vars);
	mlx_loop(vars.mlx);
}
