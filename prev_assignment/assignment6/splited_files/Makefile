SRCS	=	main.cc linkedlist.cc polynomial.cc process_IO.cc \

OBJS = $(SRCS:.cc=.o)

CC = gcc

CFALGS = -Wall -Werror -Wextra

NAME = ./a.out

all			:	$(NAME)

$(NAME)		:	$(OBJS)
				$(CC) $(CFALGS) -o $(NAME) $(OBJS)

clean		:
				rm -f $(OBJS)

fclean		:	clean
				rm -f $(NAME)
			
re			:	fclean $(NAME)

.PHONY		:	all clean fclean re