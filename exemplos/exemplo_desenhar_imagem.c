#include "mlx.h"
#include "cubfile.h"
#include "cub3d.h"





int	main(void)
{
	void *mlx;
	void *window_ptr;
	t_file *cubfile;
	t_img img;

	cubfile = ft_cubfile("./maps/1.cub");
	mlx = mlx_init();
	// window_ptr = mlx_new_window(mlx, cubfile->width, cubfile->height, "Testando Novamente");
	// img.img = mlx_new_image(mlx, cubfile->width, cubfile->height);
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
