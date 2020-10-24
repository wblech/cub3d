DIR_OBJ = .objs
DIR_SRC = src
DIR_INC = ./inc
DIR_MLX = ./minilibx-linux
DIR_LIBFT = ./libft
SRCS = 	$(DIR_SRC)/cubfile_reader/gnl/get_next_line.c \
		$(DIR_SRC)/cubfile_reader/gnl/get_next_line_utils.c \
		$(DIR_SRC)/cubfile_reader/ft_print_error_cubfile.c \
		$(DIR_SRC)/cubfile_reader/ft_check_map_cubfile_utils.c \
		$(DIR_SRC)/cubfile_reader/ft_check_map_cubfile.c \
		$(DIR_SRC)/cubfile_reader/ft_get_map_cubfile.c \
		$(DIR_SRC)/cubfile_reader/ft_malloc_map.c \
		$(DIR_SRC)/cubfile_reader/ft_get_info_value.c \
		$(DIR_SRC)/cubfile_reader/ft_cubfile.c \
		$(DIR_SRC)/cubfile_reader/ft_cubfile_utils.c \
		$(DIR_SRC)/cubfile_reader/ft_del_file.c \
		$(DIR_SRC)/my_mlx_pixel_put.c \
		$(DIR_SRC)/main.c

NAME = cub3D
OBJ = $(patsubst $(DIR_SRC)/%.c, $(DIR_OBJ)/%.o, $(SRCS))
CC = clang
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
LFLAGS = -lmlx -lm -lX11 -lXext -lbsd -lft
AR = ar -rc
RM = rm -f
LIBFT = $(DIR_LIBFT)/libft.a

$(NAME):	$(OBJ) $(LIBFT)
			$(CC) $(CFLAGS) $(OBJ) -I$(DIR_INC) -I$(DIR_MLX) -L$(DIR_MLX) -L$(DIR_LIBFT) $(LFLAGS) -o $@

$(DIR_OBJ)/%.o:	$(DIR_SRC)/%.c
				mkdir -p $(DIR_OBJ)
				mkdir -p $(DIR_OBJ)/cubfile_reader
				mkdir -p $(DIR_OBJ)/cubfile_reader/gnl
				$(CC) $(CFLAGS) -c $< -I$(DIR_INC) -I$(DIR_MLX) -o $@

$(LIBFT):
			$(MAKE) -C $(DIR_LIBFT)

all:	$(NAME)

clean:
	$(MAKE) -C $(DIR_LIBFT) clean
	$(RM) $(OBJ)

fclean:	clean
		$(MAKE) -C $(DIR_LIBFT) fclean
		$(RM) $(NAME)

re:	fclean all

debug:	$(LIBFT)
	$(CC) $(CFLAGS) $(SRCS) -I$(DIR_INC) -L$(DIR_LIBFT) $(LFLAGS) -fsanitize=address -o $@ -g


.PHONY:	all clean fclean re
