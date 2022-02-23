#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "pipex.h"

void    _child(int *fd, char **command, char *path, char **env, int file)
{
    close(fd[0]);
    dup2(file, 0);
    dup2(fd[1], 1);
    execve(path, command, env);
}

int main(int    argc, char*    argv[], char   **env) {
    if(argc != 5) {
        return 0;
    }
    int fd[2];
    if (pipe(fd) < 0)
    {
        perror("error");
    }

    int id = fork();
    char *s;
    char **command;
    command = ft_split(argv[2], ' ');
    s = check_path(env, command[0]);
    int id2;

    if(id == 0) {
        int file1 = open(argv[1], O_RDWR);
        close(fd[0]);
        dup2(file1, 0);
        dup2(fd[1], 1);
        close(file1);
        close(fd[1]);
        execve(s, command, env);
    }
    waitpid(id, 0, 0);
    id2 = fork();
    char **command2;
    command2 = ft_split(argv[3], ' ');
    s = check_path(env, command2[0]);
    if(id2 == 0)
    {
        int file2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
        close(fd[1]);
        dup2(file2, 1);
        dup2(fd[0], 0);
        close(file2);
        close(fd[0]);
        execve(s, command2, env);
    }
//    wait(NULL);
//    waitpid(id2, 0, 0);

}

//    int file1 = open(argv[1], O_RDWR);
//    int file2 = open(argv[4], O_RDWR);
//
//    dup2(file1, 0);
//
//
//
//
//    int i = 0;
//    char *s;
//    s = check_path(envp);
//    i = 0;
//    char **command;
//    command = ft_split(argv[2], ' ');
//
//    int pid = fork();
//    if(pid == 0){
//        dup2(file2, 1);
//        execve(pwd[i], command, envp);
//    }
//    else{
//        wait(NULL);
//        execve(pwd[i], command, envp);
//    }
//    return 0;
//}
// child 1: file : 0 