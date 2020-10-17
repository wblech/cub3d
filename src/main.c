#include "mlx.h"
#include "cubfile.h"

typedef struct	s_img {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

int	main(void)
{
//	void *mlx;
//	void *window_ptr;
	t_file *file;
//	t_img *img;

	file = ft_cubfile("./maps/1.cub");
	ft_del_file(file);
//	mlx = mlx_init();
//	window_ptr = mlx_new_window(mlx, file.width, file.height, "Testando Novamente");
//	img = mlx_new_image(mlx, file->width, file->height)
//	mlx_loop(mlx);

//	mlx_destroy_window(mlx, window_ptr);


	return (0);
}
