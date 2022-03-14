#ifndef PIPEX_H
# define PIPEX_H
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include<stdlib.h>
char *check_path(char **envp, char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char const *s2);
//static int	nbrarray(char const *s, char c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
void	frealltab(char **str);
char	*ft_strdup(char *s);
#endif