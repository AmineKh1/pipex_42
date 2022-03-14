
#include "pipex.h"

int main(int    argc, char*    argv[], char   **env) {
    if(argc < 4)
        return 0;
    int i;
    i = argc - 4;
    int fd[i][2];

    char *s;
    char **command;
    int j = i;
    while(j > 0) {
        if (pipe(fd[j]) < 0)
            perror("error");
        j--;
    }
    int id = fork();
    if(id == 0)
    {
        command = ft_split(argv[2], ' ');
        s = check_path(env, command[0]);
        int file1 = open(argv[1], O_RDWR);
        dup2(file1, 0);
        dup2(fd[i][1], 1);
        execve(s, command, env);
        exit(0);
    }
    waitpid(id, 0, 0);
    j = 3;
    while(i > 0)
    {
        id = fork();
        if(id == 0)
        {
            command = ft_split(argv[j], ' ');
            s = check_path(env, command[0]);
            dup2(fd[i][0], 0);
            dup2(fd[i - 1][1], 1);
            close(fd[i][1]);
            close(fd[i - 1][0]);
            execve(s, command, env);
        }
        i--;
        j++;
        waitpid(id, 0, 0);
    }
    waitpid(id, 0, 0);
    int id2 = fork();
    if (id2 == 0)
    {
        command = ft_split(argv[j], ' ');
        s = check_path(env, command[0]);
        int file2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
        dup2(file2, 1);
        dup2(fd[0][0], 0);
        close(fd[0][1]);
        execve(s, command, env);
    }
    waitpid(id2, 0, 0);

}
