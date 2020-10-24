#include "mlx.h"
#include "cubfile.h"
#include "cub3d.h"





int	main(int argc, char **argv)
{
	void *mlx;
	void *window_ptr;
	t_file *cubfile;
	t_img img;

	if (argc < 2)
	{
		ft_putstr("Error:\nSecond argument must be a path to the map");
		return (1);
	}

	cubfile = ft_cubfile(argv[1]);
	mlx = mlx_init();
	window_ptr = mlx_new_window(mlx, (*cubfile).width, (*cubfile).height, "Testando Novamente");
	img.img = mlx_new_image(mlx, (*cubfile).width, (*cubfile).height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
									&img.line_length, &img.endian);

	int i = 0;
	while(i < 100)
	{

		my_mlx_pixel_put(&img, 100 + i, 100, 0x00ff0000);
		my_mlx_pixel_put(&img, 100 + i, 101, 0x00ff0000);
		i++;
	}

	mlx_put_image_to_window(mlx, window_ptr, img.img, 0, 0);

	mlx_loop(mlx); //tem que ficar na main

	// ft_del_file(cubfile);
	// mlx_destroy_window(mlx, window_ptr);


	return (0);
}
