DIR_OBJ = .objs
DIR_SRC = src
DIR_LIB = lib
DIR_MLX = ./minilibx-linux
SRCS = 	$(DIR_SRC)/ft_utils.c \
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
		$(DIR_SRC)/main.c

NAME = main
LIB_NAME = libcub3d.a
OBJ = $(patsubst $(DIR_SRC)/%.c, $(DIR_OBJ)/%.o, $(SRCS))
CC = clang
CFLAGS = -Wall -Werror -Wextra
LFLAGS = -lmlx -lm -lX11 -lXext -lbsd
AR = ar -rc
RM = rm -f

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -I. -I$(DIR_MLX) -L$(DIR_MLX) -L. $(LFLAGS) -o $@ -g

$(DIR_OBJ)/%.o:	$(DIR_SRC)/%.c
				mkdir -p $(DIR_OBJ)
				$(CC) $(CFLAGS) -c $< -I. -I$(DIR_MLX) -o $@

all:	$(NAME)

clean:
	$(RM) $(OBJ)

fclean:	clean
		$(RM) $(LIB_NAME)
		$(RM) $(NAME)

re:	fclean all

test:	otest
			$(CC) $(CFLAGS) test.o -I. -I$(DIR_MLX) -L$(DIR_MLX) -L. $(LFLAGS) -o $@ -g
			./test

otest:
				$(CC) $(CFLAGS) -c ./src/test.c -I. -I$(DIR_MLX) -o test.o


.PHONY:	all clean fclean re
