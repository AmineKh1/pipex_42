#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
char *check_path(char **envp, char *s);
#endif