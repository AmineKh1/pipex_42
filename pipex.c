/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhouya <akhouya@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:38:10 by akhouya           #+#    #+#             */
/*   Updated: 2022/03/22 11:38:51 by akhouya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char **env)
{
	struct attribut	attribut;

	if (argc != 5)
		exit(1);
	table(&attribut);
	handling_errors(&attribut, argc, argv);
	while (attribut.i <= argc - 2)
	{
		command_evec(&attribut, env, argv);
		if (pipe(attribut.fd) < 0)
		{
			perror(NULL);
			close_pipe(&attribut, argv);
			exit(1);
		}
		attribut.pid = fork();
		if (attribut.pid == -1)
			return (1);
		if (attribut.pid == 0)
			child_proc(attribut, argv, env, argc);
		else
			parent_poc(&attribut);
	}
	close_pipe(&attribut, argv);
}
