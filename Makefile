SRCS = printf.c

NAME = libftprintf.a

CC = gcc

LIBS = -L./libft -lft

CFLAGS = -Wall -Wextra -Werror

build_libft :
	$(MAKE) -C libft/

all : $(NAME)

OBJS = $(SRCS:.c=.o)

$(NAME): build_libft $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
