SRCS = ft_printf.c ft_buf_sizing.c ft_parsing.c

OBJS = $(SRCS:.c=.o)

NAME = libftprintf.a

CC = gcc

LIBS = -L./libft -lft

CFLAGS = -g3 -Wall -Wextra -Werror 

LIBFT = libft/libft.a

INCLUDES = -I libft/includes

LIBS = -L libft -lft

all : $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	cp $(LIBFT) $(NAME)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

$(LIBFT) :
	$(MAKE) -C libft/

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $< -c

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
