/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_proc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhouya <akhouya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 18:26:45 by akhouya           #+#    #+#             */
/*   Updated: 2022/03/31 14:25:22 by akhouya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	in_child(t_attribut attribut, char **argv, char **env)
{
	put_error(attribut, argv[attribut.i]);
	if (attribut.in == -1)
		exit(1);
	dup2(attribut.in, 0);
	dup2(attribut.fd[1], 1);
	close(attribut.fd[0]);
	execve(attribut.s, attribut.command, env);
	exit(1);
}

void	out_child(t_attribut attribut, char **argv, char **env)
{
	put_error(attribut, argv[attribut.i]);
	dup2(attribut.fd_in, 0);
	dup2(attribut.out, 1);
	close(attribut.fd[1]);
	close(attribut.fd[0]);
	execve(attribut.s, attribut.command, env);
	exit(1);
}

void	pipe_child(t_attribut attribut, char **argv, char **env)
{
	put_error(attribut, argv[attribut.i]);
	dup2(attribut.fd_in, 0);
	dup2(attribut.fd[1], 1);
	close(attribut.fd[0]);
	execve(attribut.s, attribut.command, env);
	exit(1);
}

void	parent_poc(t_attribut *attribut)
{
	close(attribut->fd[1]);
	attribut->fd_in = attribut->fd[0];
	attribut->i++;
	attribut->tab[attribut->i - 3 - attribut->h] = attribut->fd[0];
}

void	child_proc(t_attribut attribut, char **argv, char **env, int argc)
{
	if (attribut.i - attribut.h == 2)
		in_child(attribut, argv, env);
	else if (attribut.i == argc - 2)
		out_child(attribut, argv, env);
	else
		pipe_child(attribut, argv, env);
}
