SRCS = ft_printf.c ft_buf_sizing.c ft_parsing.c

OBJS = $(SRCS:.c=.o)

NAME = libftprintf.a

CC = gcc

LIBS = -L./libft -lft

CFLAGS = -Wall -Wextra -Werror 

LIBFT = libft/libft.a

INCLUDES = -I libft/includes

LIBS = -L libft/ -lft

all : $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	cp $(LIBFT) $(NAME)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

$(LIBFT) :
	$(MAKE) -C libft/

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $< -c

clean:
	$(MAKE) clean -C libft/
	rm -f $(OBJS)

fclean:	clean
	$(MAKE) fclean -C libft/
	rm -f $(NAME)

re:	fclean all
	$(MAKE) re -C libft/

.PHONY: all clean fclean re
