
#include "pipex.h"

void	put_error(char *s1, char *s2)
{
	char *s;
	s = ft_strjoin(s1, s2);
	ft_putstr_fd(s, 2);
	exit(1);
}

void	in_child(struct attribut	attribut, char **argv, char **env,int argc)
{
	if(attribut.s == NULL)
		put_error("pipex: %s: command not found\n", argv[attribut.i]);
	dup2(attribut.in, 0);
	dup2(attribut.fd[1], 1);
	close(attribut.fd[0]);
	execve(attribut.s, attribut.command, env);
}

void	out_child(struct attribut	attribut, char **argv, char **env,int argc)
{
	attribut.out = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if(attribut.s == NULL)
		put_error("pipex: %s: command not found\n", argv[attribut.i]);
	dup2(attribut.fd_in, 0);
	dup2(attribut.out, 1);
	close(attribut.fd[1]);
	close(attribut.fd[0]);
	execve(attribut.s, attribut.command, env);
}

void	pipe_child(struct attribut	attribut, char **argv, char **env)
{
	if(attribut.s == NULL)
	{
		put_error("pipex: %s: command not found\n", argv[attribut.i]);
	}
	dup2(attribut.fd_in, 0);
	dup2(attribut.fd[1], 1);
	close(attribut.fd[0]);
	execve(attribut.s, attribut.command, env);
}

void parent_poc(struct attribut	*attribut)
{
	close(attribut->fd[1]);
	attribut->fd_in = attribut->fd[0];
	attribut->i++;
	attribut->tab[attribut->i - 3] = attribut->fd[0];  
}

void	command_evec(struct attribut	*attribut, char **env,char **argv)
{
	if (!(strcmp(argv[attribut->i],"")))
		exit(1);
	if (access(argv[attribut->i], F_OK) == 0)
	{
		attribut->command = ft_split(argv[attribut->i], ' ');
		attribut->s = attribut->command[0];
		return ;
	}
	attribut->command = ft_split(argv[attribut->i], ' ');
	attribut->s = check_path(env, attribut->command[0]);
}

void	child_proc(struct attribut attribut, char	**argv, char	**env, int	argc)
{
	if(attribut.i == 2)
		in_child(attribut, argv, env, argc);
	else if(attribut.i == argc - 2)
		out_child(attribut, argv, env, argc);
	else
		pipe_child(attribut, argv, env);
}

int	main(int	argc, char*	argv[], char   **env) 
{
	struct attribut	attribut;

	attribut.fd_in = 0;
	attribut.in = open(argv[1], O_RDWR);
	attribut.i = 2;
	if (attribut.in == -1)
		put_error("pipex: no such file or directory: %s", argv[1]);
	if(argc < 5)
		return 1;
	while(attribut.i <= argc - 2)
	{
		command_evec(&attribut, env, argv);
		pipe(attribut.fd);
		if((attribut.pid = fork()) == -1)
			return 1;
		if(attribut.pid == 0)
			child_proc(attribut, argv, env, argc);
		else
			parent_poc(&attribut);
	}
	while(wait(NULL) != -1)
	attribut.i = attribut.i - 3;
	while(attribut.i >= 0)
		close(attribut.tab[attribut.i--]);
}
