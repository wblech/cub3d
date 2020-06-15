DIR_OBJ = .objs
DIR_SRC = src
DIR_LIB = lib
DIR_MLX = ./minilibx-linux
DIR_INC = ./inc
DIR_LIBFT = ./libft
SRCS = 	$(DIR_SRC)/gnl/get_next_line.c \
		$(DIR_SRC)/gnl/get_next_line_utils.c \
		$(DIR_SRC)/ft_utils.c \
		$(DIR_SRC)/ft_adt.c \
		$(DIR_SRC)/ft_circle.c \
		$(DIR_SRC)/ft_line.c \
		$(DIR_SRC)/ft_trgb.c \
		$(DIR_SRC)/ft_quadrilateral.c \
		$(DIR_SRC)/ft_player.c \
		$(DIR_SRC)/win_update.c \
		$(DIR_SRC)/ft_vars.c \
		$(DIR_SRC)/ft_image.c \
		$(DIR_SRC)/ft_map.c \
		$(DIR_SRC)/ft_color.c \
		$(DIR_SRC)/ft_raycast.c \
		$(DIR_SRC)/ft_texture.c \
		$(DIR_SRC)/ft_draw_2d_3d_map.c \
		$(DIR_SRC)/ft_check_map_cubfile_utils.c \
		$(DIR_SRC)/ft_check_map_cubfile.c \
		$(DIR_SRC)/ft_get_map_cubfile.c \
		$(DIR_SRC)/ft_malloc_map.c \
		$(DIR_SRC)/ft_print_error.c \
		$(DIR_SRC)/ft_get_info_value.c \
		$(DIR_SRC)/ft_cubfile.c \
		$(DIR_SRC)/ft_cubfile_utils.c \
		$(DIR_SRC)/main.c

NAME = main
LIB_NAME = libcub3d.a
OBJ = $(patsubst $(DIR_SRC)/%.c, $(DIR_OBJ)/%.o, $(SRCS))
CC = clang
CFLAGS = -Wall -Werror -Wextra
LFLAGS = -lmlx -lm -lX11 -lXext -lbsd -lft
AR = ar -rc
RM = rm -f
LIBFT = $(DIR_LIBFT)/libft.a

$(NAME):	$(OBJ) $(LIBFT)
			$(CC) $(CFLAGS) $(OBJ) -I$(DIR_INC) -I$(DIR_MLX) -L$(DIR_MLX) -L$(DIR_LIBFT) $(LFLAGS) -o $@ -g

$(DIR_OBJ)/%.o:	$(DIR_SRC)/%.c
				mkdir -p $(DIR_OBJ)
				mkdir -p $(DIR_OBJ)/gnl
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

test:	otest
			$(CC) $(CFLAGS) test.o -I. -I$(DIR_MLX) -L$(DIR_MLX) -L. $(LFLAGS) -o $@ -g
			./test

otest:
		$(CC) $(CFLAGS) -c ./src/test.c -I. -I$(DIR_MLX) -o test.o


.PHONY:	all clean fclean re
