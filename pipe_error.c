/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhouya <akhouya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 18:37:11 by akhouya           #+#    #+#             */
/*   Updated: 2022/03/31 13:56:42 by akhouya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	put_error(t_attribut attribut, char *s2)
{
	if (attribut.s == NULL)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(s2, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
}

void	put_error_fd(char *s2)
{
	ft_putstr_fd("pipex: no such file or directory: ", 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd("\n", 2);
}

void	put_error_fd_out(char *s2)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(": Permission denied", 2);
	ft_putstr_fd("\n", 2);
}

void	command_evec(t_attribut *attribut, char **env, char **argv)
{
	if (!(ft_strncmp(argv[attribut->i], "", 1)))
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(argv[attribut->i], 2);
		ft_putstr_fd(": command not found\n", 2);
		attribut->tab_err[127] = 1;
		return ;
	}
	if (access(argv[attribut->i], F_OK) == 0)
	{
		attribut->command = ft_split(argv[attribut->i], ' ');
		attribut->s = attribut->command[0];
		return ;
	}
	attribut->command = ft_split(argv[attribut->i], ' ');
	attribut->s = check_path(env, attribut->command[0]);
	if (attribut->s == NULL)
		attribut->tab_err[127] = 1;
}

void	handling_errors(t_attribut *attribut, int argc, char **argv)
{
	attribut->out = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (ft_strncmp("here_doc", argv[1], 8) == 0)
	{
		attribut->in = open("herdoc.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
		pipe_herdoc(attribut, argv);
		close(attribut->in);
		attribut->in = open("herdoc.txt", O_RDWR);
		attribut->i = 3;
		attribut->h = 1;
	}
	else
	{
		attribut->in = open(argv[1], O_RDWR);
		attribut->i = 2;
		attribut->h = 0;
	}
	
	if (attribut->in == -1)
		put_error_fd(argv[1]);
	if (attribut->out == -1)
	{
		put_error_fd_out(argv[argc - 1]);
		exit(1);
	}
}
