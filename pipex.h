/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhouya <akhouya@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 10:45:23 by akhouya           #+#    #+#             */
/*   Updated: 2022/03/18 18:43:39 by akhouya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include<stdlib.h>
struct attribut {
    int fd[2];
    pid_t pid;
    int fd_in;
    char *s;
    char **command;
    int tab[1024];
    int i;
    int in;
    int out;
} t_attribut;
char *check_path(char **envp, char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2);
//static int	nbrarray(char const *s, char c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
void	frealltab(char **str);
char	*ft_strdup(char *s);
void	ft_putstr_fd(char *s, int fd);
void	put_error(struct attribut attribut, char *s2);
 void	ft_putchar_fd(char c, int fd);
#endif