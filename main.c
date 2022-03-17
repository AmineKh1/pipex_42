
#include "pipex.h"

// optimise my code

int main(int    argc, char*    argv[], char   **env) {
    if(argc != 5)
        return 0;
    int fd[2];
    if (pipe(fd) < 0)
        perror("error");
    int id = fork();
    char *s;
    char **command;
    int id2;
    if(id == 0) {
        command = ft_split(argv[2], ' ');
        s = check_path(env, command[0]);
        int file1 = open(argv[1], O_RDWR);
        if(s == NULL)
        {
            printf("pipex: %s: command not found\n", argv[2]);
            exit(0);
        }
        close(fd[0]);
        dup2(file1, 0);
        dup2(fd[1], 1);
        close(file1);
        close(fd[1]);
        execve(s, command, env);
    }
    id2 = fork();
    char **command2;

    if(id2 == 0)
    {
        command2 = ft_split(argv[3], ' ');
        s = check_path(env, command2[0]);
        int file2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
        if(s == NULL)
        {
            printf("pipex: %s: command not found\n", argv[3]);
            exit(0);
        }
        close(fd[1]);
        dup2(file2, 1);
        dup2(fd[0], 0);
        close(file2);
        close(fd[0]);
        execve(s, command2, env);
    }
}
