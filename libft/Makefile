SRCS = ft_bzero.c \
	  ft_memccpy.c \
	  ft_memcpy.c \
	  ft_memmove.c \
	  ft_memset.c \
	  ft_strlen.c \
	  ft_memchr.c \
	  ft_memcmp.c \
	  ft_strlcat.c \
	  ft_strchr.c \
	  ft_strrchr.c \
	  ft_strnstr.c \
	  ft_strncmp.c \
	  ft_isascii.c \
	  ft_atoi.c \
	  ft_isdigit.c \
	  ft_isspace.c \
	  ft_isalpha.c \
	  ft_isalnum.c \
	  ft_isprint.c \
	  ft_isupper.c \
	  ft_islower.c \
	  ft_toupper.c \
	  ft_tolower.c \
	  ft_calloc.c \
	  ft_strlcpy.c \
	  ft_strdup.c \
	  ft_substr.c \
	  ft_strjoin.c \
	  ft_strtrim.c \
	  ft_strncpy.c \
	  ft_split.c \
	  ft_chartostr.c \
	  ft_itoa.c \
	  ft_newstr.c \
	  ft_strmapi.c \
	  ft_putchar_fd.c \
	  ft_putstr_fd.c \
	  ft_putendl_fd.c \
	  ft_putnbr_fd.c
OBJS = $(SRCS:.c=.o)
SRCS_BONUS = ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
NAME = libft.a
HEADER = libft.h
RM = rm -f
CC = gcc
CFLAGS = -Wall -Werror -Wextra

all:	$(NAME)

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

$(NAME):	$(OBJS) $(HEADER)
	ar -rc $(NAME) $(OBJS)
	ranlib $(NAME)

bonus:	$(OBJS) $(OBJS_BONUS) $(HEADER)
	ar -rc $(NAME) $(OBJS) $(OBJS_BONUS)
	ranlib $(NAME)

.c.o:
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

.PHONY:	all clean fclean re


