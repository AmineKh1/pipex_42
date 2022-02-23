NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC =  main.c pipex_utils.c
all: ${NAME}

${NAME}:
		make -C "libft/"
		cp libft/libft.a ./
		${CC} ${CFLAGS} ${SRC} libft.a -o ${NAME}

RM = rm -rf



clean:
	@${RM} ${OBJ}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: clean all bonus fclean re