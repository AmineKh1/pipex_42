
#include "pipex.h"
#include <string.h>

void	table(struct attribut *attribut)
{
	int i = 0;
	while (i < 255)
		attribut->tab_err[i++] = 0;
}
void	pipe_herdoc(struct attribut *attribut)
{
	char *s;
	char *str;

	s = get_next_line(0);
	str = ft_strdup("");
	while(strcmp("LIMITER\n", s) != 0)
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

void	child_proc(struct attribut attribut, char	**argv, char	**env, int	argc)
{
	if (attribut.i == 2)
		in_child(attribut, argv, env, argc);
	else if (attribut.i == argc - 2)
		out_child(attribut, argv, env, argc);
	else
		pipe_child(attribut, argv, env);
}

void	handling_errors(struct attribut	*attribut, int argc, char **argv)
{
	table(attribut);
	attribut->fd_in = 0;
	attribut->out = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if(strcmp("LIMITER", argv[1]) == 0)
	{
		attribut->in = open("herdoc.txt", O_RDWR | O_CREAT | O_TRUNC , 0644);
		pipe_herdoc(attribut);
		close(attribut->in);
		attribut->in = open("herdoc.txt", O_RDWR);
	}
	else
		attribut->in = open(argv[1], O_RDWR);
	attribut->i = 2;
	if (argc < 5)
		exit(1);
	if (attribut->in == -1)
		put_error_fd(argv[1]);
	if (attribut->out == -1)
	{
		put_error_fd_out(argv[argc - 1]);
		exit(1);
	}
}
int	main(int	argc, char*	argv[], char   **env) 
{
	struct attribut	attribut;

	handling_errors(&attribut, argc, argv);
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
	while (wait(NULL) != -1);
	attribut.i = attribut.i - 3;
	while (attribut.i >= 0)
		close(attribut.tab[attribut.i--]);
	close(attribut.in);
	if(strcmp("herdoc", argv[1]) == 0)
		unlink("herdoc.txt");
	if(attribut.tab_err[127] == 1)
		exit(127);
}
