
#include "pipex.h"

// char *command_exec(char **command, char **env){
//     char *s;
//     command = ft_split(argv[i], ' ');
//     s = check_path(env, command[0]);
//     return s;
// }
int main(int    argc, char*    argv[], char   **env) {
    int fd[2];
    pid_t pid;
    int fd_in;
    fd_in = 0;
    int i;
    i = 2;
    char *s;
    char **command;
    int tab[1024];
    if(argc < 5)
        return 0;
    while(i <= argc - 2)
    {
        command = ft_split(argv[i], ' ');
        s = check_path(env, command[0]);
        printf("%s\n", s);
        pipe(fd);
        if((pid = fork()) == -1)
            exit(1);
        if(pid == 0)
        {
            if(i == 2)
            {
                int file1 = open(argv[1], O_RDWR);
                if(s == NULL)
                {
                    printf("pipex: %s: command not found\n", argv[i]);
                    exit(0);
                }
                dup2(file1, 0);
                dup2(fd[1], 1);
                close(fd[0]);
                execve(s, command, env);
            }
            else if(i == argc - 2)
            {
                int file2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
                if(s == NULL)
                {
                    printf("pipex: %s: command not found\n", argv[i]);
                    exit(0);
                }
                dup2(fd_in, 0);
                dup2(file2, 1);
                close(fd[1]);
                close(fd[0]);
                execve(s, command, env);
            }
            else
            {
                if(s == NULL)
                {
                    printf("pipex: %s: command not found\n", argv[i]);
                    exit(0);
                }
                dup2(fd_in, 0);
                dup2(fd[1], 1);
                close(fd[0]);
                execve(s, command, env);
            }
        }
        else{
            close(fd[1]);
            fd_in = fd[0];
            i++;
            tab[i - 3] = fd[0];
            
        }

    }
    while(wait(NULL) != -1)
    i = i - 3;
    while(i >= 0)
        close(tab[i--]);
    
}
