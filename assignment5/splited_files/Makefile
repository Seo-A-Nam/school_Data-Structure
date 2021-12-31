SRCS	=	stack.cc check_input.cc convert_to_postfix.cc \
			calculate.cc main.cc \

OBJS	=	$(SRCS:.c=.o)

CC		=	g++

NAME	=	a.out

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean	:
			rm -f $(OBJS)

fclean	:	clean
			rm -f $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re


