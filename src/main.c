#include "mlx.h"
#include "cubfile.h"


int	main(void)
{
	void *mlx;
	void *window_ptr;
	t_file *file;

	file = ft_cubfile("./maps/1.cub");
	mlx = mlx_init();
	window_ptr = mlx_new_window(mlx, file->width, file->height, "Testando Novamente");
	mlx_loop(mlx);
//	mlx_destroy_window(mlx, window_ptr);


	return (0);
}

