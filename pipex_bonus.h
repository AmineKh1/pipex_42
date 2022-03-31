/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhouya <akhouya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:06:45 by akhouya           #+#    #+#             */
/*   Updated: 2022/03/31 18:32:04 by akhouya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include<stdlib.h>

typedef struct s_attribut
{
	int		fd[2];
	pid_t	pid;
	int		fd_in;
	char	*s;
	char	**command;
	int		tab[1024];
	int		i;
	int		in;
	int		out;
	int		tab_err[255];
	int		h;
}	t_attribut;
char	*check_path(char **envp, char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
void	frealltab(char **str);
char	*ft_strdup(char *s);
void	ft_putstr_fd(char *s, int fd);
void	put_error(t_attribut attribut, char *s2);
void	ft_putchar_fd(char c, int fd);
char	*ft_strjoin_free(char *s, char c);
char	*get_next_line(int fd);
void	put_error(t_attribut attribut, char *s2);
void	put_error_fd(char *s2);
void	put_error_fd_out(char *s2);
void	command_evec(t_attribut *attribut, char **env, char **argv);
void	in_child(t_attribut attribut, char **argv, char **env);
void	out_child(t_attribut attribut, char **argv, char **env);
void	pipe_child(t_attribut attribut, char **argv, char **env);
void	parent_poc(t_attribut *attribut);
void	child_proc(t_attribut attribut, char **argv, char **env, int argc);
void	handling_errors(t_attribut *attribut, int argc, char **argv);
void	pipe_herdoc(t_attribut *attribut, char **argv);
void	table(t_attribut *attribut);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	close_pipe(t_attribut *attribut, char **argv);
#endif