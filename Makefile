VPATH= utils
NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC =  pipex.c pipex_utils.c pipex_proc.c pipe_error.c utils/ft_putstr_fd.c utils/ft_split.c utils/ft_strdup.c utils/ft_strjoin.c utils/ft_strlen.c utils/ft_strncmp.c utils/ft_substr.c utils/get_next_line.c
OBJ = ${SRC:.c=.o}
OBJB = ${SRC:.c=.o}
RM = rm -rf

all: ${NAME}

${NAME}: ${OBJ}
bonus: ${OBJB}
%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@
	ar -rc ${NAME} $@
clean:
	@${RM} ${OBJ} ${OBJB}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: clean all bonus fclean re