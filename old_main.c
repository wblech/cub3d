#include "cub3d.h"

typedef struct s_vars
{
	void *mlx;
	void *win;
} t_vars;

int line(int x, int y, t_vars *vars)
{
	t_point start;
	t_point end;
	t_data img;

	start = ft_create_point(300, 300, 0x00ff0000);
	end = ft_create_point(x, y, 0x00ff0000);
	// printf("mouse: (%i, %i)\n", x, y);
	// printf("mouse: (%i, %i)\n", x, y);
	img.img = mlx_new_image(vars->mlx, 600, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	ft_line_dda(&img, start, end);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	return (0);
}

int main(void)
{
	t_vars vars;
	// t_data img;
	// int x;
	// int y;
	// char *relative_path = "./img/redbrick.XPM";
	// int img_width;
	// int img_height;

	// x = 0;
	// y = 0;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 600, 600, "Hook");

	// img.img = mlx_xpm_file_to_image(vars.mlx, relative_path, &img_height, &img_width);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	// while ( y <= 600)
	// {
	// 	while (x <= 600)
	// 	{
	// 		mlx_put_image_to_window(vars.mlx, vars.win, img.img, x, y);
	// 		x += 60;
	// 	}
	// 	x = 0;
	// 	y += 60;
	// }
	mlx_hook(vars.win, 6, 1L << 6, line, &vars);

	mlx_loop(vars.mlx);
}
