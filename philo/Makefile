NAME  = philo

SRCS	=	./lib_utils.c \
			./ft_putstr_fd.c \
			./parsing.c \
			./threading.c \
			./utils.c \
			./philo_utils.c \
			./checking.c \
			./start_thread.c \
			./main.c



OBJS= $(SRCS:.c=.o)

INC	=	-I inc

CC	=	gcc

CFLAGS	=	-Wall -Werror -Wextra -g -pthread #-fsanitize=address
.c.o	:
			${CC} ${CFLAGS} ${INC} -c $< -o ${<:.c=.o}

all : ${NAME}

$(NAME) :	${OBJS}
			${CC} $(CFLAGS) -o $(NAME) $(OBJS)


clean	:	
			rm -rf ${OBJS}

fclean	:	clean
			rm -rf ${NAME}

re		:	fclean all

.PHONY	:	all clean fclean re