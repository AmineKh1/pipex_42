NAME = pipex
NAMEB = pipex_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC =  pipex.c pipex_utils.c pipex_proc.c pipe_error.c utils/ft_putstr_fd.c utils/ft_split.c utils/ft_strdup.c utils/ft_strjoin.c utils/ft_strlen.c utils/ft_strncmp.c utils/ft_substr.c utils/get_next_line.c
SRCB =  pipex_bonus.c pipex_utils.c pipex_proc.c pipe_error.c utils/ft_putstr_fd.c utils/ft_split.c utils/ft_strdup.c utils/ft_strjoin.c utils/ft_strlen.c utils/ft_strncmp.c utils/ft_substr.c utils/get_next_line.c
OBJ = ${SRC:.c=.o}
OBJB = ${SRCB:.c=.o}
RM = rm -rf

all: ${NAME}

${NAME}: ${OBJ}
	${CC} ${OBJ} -o ${NAME}
${NAMEB}: ${OBJB}
	${CC} ${OBJB} -o ${NAMEB}
bonus: ${NAMEB}
%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@
clean:
	@${RM} ${OBJ} ${OBJB}

fclean: clean
	@${RM} ${NAME} ${NAMEB}

re: fclean all
rebonus: fclean bonus
.PHONY: clean all bonus fclean re rebonus