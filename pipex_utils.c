/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhouya <akhouya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 18:29:37 by akhouya           #+#    #+#             */
/*   Updated: 2022/03/31 13:55:41 by akhouya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	split_join(char **pwd, int i, char *s)
{
	while (pwd[++i])
		pwd[i] = ft_strjoin(pwd[i], "/");
	i = -1;
	while (pwd[++i])
		pwd[i] = ft_strjoin(pwd[i], s);
	i = -1;
	while (pwd[++i] != NULL)
	{
		if (access(pwd[i], F_OK) == 0)
			break ;
	}
	return (i);
}

char	*check_path(char **envp, char *s)
{
	int		i;
	char	**pwd;
	char	*path;

	i = -1;
	while (envp[++i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			break ;
	}
	if (envp[i] == NULL)
		return (NULL);
	path = &envp[i][5];
	pwd = ft_split(path, ':');
	i = -1;
	i = split_join(pwd, i, s);
	if (pwd[i])
		path = ft_strdup(pwd[i]);
	else
		path = NULL;
	frealltab(pwd);
	free(pwd);
	return (path);
}

void	table(t_attribut *attribut)
{
	int	i;

	i = 0;
	while (i < 255)
		attribut->tab_err[i++] = 0;
}

void	pipe_herdoc(t_attribut *attribut, char **argv)
{
	char	*s;
	char	*str;
	char	*herdoc;

	write(0, "heredoc>", 8);
	s = get_next_line(0);
	herdoc = ft_strjoin(argv[2], "\n");
	while (ft_strncmp(herdoc, s, ft_strlen(herdoc)) != 0)
	{
		write(0, "heredoc>", 8);
		write(attribut->in, s, ft_strlen(s));
		free(s);
		s = get_next_line(0);
	}
	if (ft_strncmp("", s, 1) == 0)
	{
		free(s);
		free(herdoc);
		str = NULL;
		return ;
	}
	free(s);
	free(herdoc);
}

void	close_pipe(t_attribut *attribut, char **argv)
{
	attribut->i = attribut->i - 3 - attribut->h;
	while (attribut->i >= 0)
		close(attribut->tab[attribut->i--]);
	close(attribut->in);
	if (ft_strncmp("here_doc", argv[1], 8) == 0)
		unlink("herdoc.txt");
	if (attribut->tab_err[127] == 1)
		exit(127);
}
