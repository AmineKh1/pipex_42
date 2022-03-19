
#include "pipex.h"
#include <string.h>

void	pipe_herdoc(struct attribut *attribut)
{
	char *s;
	char *str;

	s = get_next_line(0);
	str = ft_strdup("");
	while(strcmp("herdoc\n", s) != 0)
	{
		str = ft_strjoin(str, s);
		free(s);
		s = get_next_line(0);
	}
	if (strcmp("", str) == 0)
	{
		free(s);
		free(str);
		str = NULL;
	}
	write(attribut->in, str, ft_strlen(str));
	free(str);
	free(s);
}

void	put_error(struct attribut attribut, char *s2)
{
	if (attribut.s == NULL)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(s2, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(1);
	}
}

void	put_error_fd(char *s2)
{
	ft_putstr_fd("pipex: no such file or directory: ", 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd("\n", 2);
}

void	in_child(struct attribut	attribut, char **argv, char **env,int argc)
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

void	out_child(struct attribut	attribut, char **argv, char **env,int argc)
{
	attribut.out = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	put_error(attribut, argv[attribut.i]);
	dup2(attribut.fd_in, 0);
	dup2(attribut.out, 1);
	close(attribut.fd[1]);
	close(attribut.fd[0]);
	execve(attribut.s, attribut.command, env);
	exit(1);
}

void	pipe_child(struct attribut	attribut, char **argv, char **env)
{
	put_error(attribut, argv[attribut.i]);
	dup2(attribut.fd_in, 0);
	dup2(attribut.fd[1], 1);
	close(attribut.fd[0]);
	execve(attribut.s, attribut.command, env);
	exit(1);
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
	if (attribut.i == 2)
		in_child(attribut, argv, env, argc);
	else if (attribut.i == argc - 2)
		out_child(attribut, argv, env, argc);
	else
		pipe_child(attribut, argv, env);
}

int	main(int	argc, char*	argv[], char   **env) 
{
	struct attribut	attribut;

	attribut.fd_in = 0;
	if(strcmp("herdoc", argv[1]) == 0)
	{
		attribut.in = open("herdoc.txt", O_RDWR | O_CREAT | O_TRUNC , 0644);
		pipe_herdoc(&attribut);
		close(attribut.in);
		attribut.in = open("herdoc.txt", O_RDWR);
	}
	else
		attribut.in = open(argv[1], O_RDWR);
	attribut.i = 2;
	if (argc < 5)
		return (1);
	if (attribut.in == -1)
		put_error_fd(argv[1]);
	while (attribut.i <= argc - 2)
	{
		command_evec(&attribut, env, argv);
		pipe(attribut.fd);
		if ((attribut.pid = fork()) == -1)
			return (1);
		if (attribut.pid == 0)
			child_proc(attribut, argv, env, argc);
		else
			parent_poc(&attribut);
	}
	while (wait(NULL) != -1)
	attribut.i = attribut.i - 3;
	while (attribut.i >= 0)
		close(attribut.tab[attribut.i--]);
	if(strcmp("herdoc", argv[1]) == 0)
		unlink("herdoc.txt");
}
