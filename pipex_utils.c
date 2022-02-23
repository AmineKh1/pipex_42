#include "pipex.h"
#include <fcntl.h>
#include <unistd.h>
char *check_path(char **envp, char *s)
{
    int i;
    char **pwd;
    char *path;

    i = 0;
    while (envp[i] != NULL)
    {
        if(ft_strncmp(envp[i], "PATH", 4) == 0) {
            break;
        }
        i++;
    }
    path = &envp[i][5];
    pwd = ft_split(path,':');
    i= 0;
    while(pwd[i])
    {
        pwd[i] = ft_strjoin(pwd[i], "/");
        i++;
    }
    i = 0;
    while(pwd[i])
    {
        pwd[i] = ft_strjoin(pwd[i], s);
        i ++;
    }

    i = 0;
    while(pwd[i] != NULL)
    {

        if(access(pwd[i], F_OK) == 0)
            break;
        i++;
    }
    return pwd[i];
}
