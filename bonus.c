#include "pipex.h"

// void closePipe(int fd[][2],int i)
// {
//     int j;
//     j = 0;
//     while(j > i)
//     {
//         close(fd[j][0]);
//         close(fd[j][1]);
//         j++;
//     }
// }


void    loop_pipe(char ***cmd)
{
    int   p[2];
    pid_t pid;
    int   fd_in = 0;
    while (*cmd != NULL)
    {
        
        pipe(p);
        if ((pid = fork()) == -1)
        {
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {

            dup2(fd_in, 0); 
            if (*(cmd + 1) != NULL)
                dup2(p[1], 1);
            close(p[0]);
            
            execvp((*cmd)[0], *cmd);
            exit(EXIT_FAILURE);
        }
        else
        {
            wait(NULL);
            close(p[1]);
            printf("%d, %d, %d\n", p[0], fd_in, p[1]);
            fd_in = p[0];
            
            cmd++;
        }
    }
}
// i should open multiple pipe argc - 4 and close all pipes, keep checking the command and the firl file in at argc 1 and laste file out argc - 1
// void pipe_fork(int fd[2], int fIn, int fOut, char *s, char **command, int i){
//     pipe(fd);
//     int id = fork();
//     if(id == 0){
//         command = ft_split(argv[2], ' ');
//         s = check_path(env, command[0]);
//         dup2(fd[0], 0);
//         dup2(fd[1], 1);
//         close(fd[0]);
//         close(fd[1]);
//     }
// }

// int main(int argc, char **argv, char **env)
// {
//     if(argc < 4)
//         return 1;
//     int fd[argc - 4][2];
//     char *s;
//     char **command;
//     int fIn = open(argv[1], O_RDWR);
//     int fOut = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
//     int i = 2;
//     id = fork();
//     pipe(fd);
//     if(id == 0) {
//         command = ft_split(argv[2], ' ');
//         s = check_path(env, command[0]);
//         int file1 = open(argv[1], O_RDWR);
//         if(s == NULL)
//         {
//             printf("pipex: %s: command not found\n", argv[2]);
//             exit(0);
//         }
//         close(fd[0]);
//         dup2(file1, 0);
//         dup2(fd[1], 1);
//         close(file1);
//         close(fd[1]);
//         execve(s, command, env);
//     }
//     else{
//         wait(NULL);
//         close(fd[0]);
//         close(fd[1]);
//     }
//     while(i < argc - 2)
//     {
//         pipe_fork(fd, fIn, fOut, s, command, i);
//         i++;
//     }
// }
int main()
{
  char *ls[] = {"ls", NULL};
  char *grep[] = {"grep", "pipe", NULL};
  char *wc[] = {"wc", NULL};
  char *wcs[] = {"ls", 0};
  char **cmd[] = {ls, grep, wc, wcs, NULL};

  loop_pipe(cmd);
  return (0);
}