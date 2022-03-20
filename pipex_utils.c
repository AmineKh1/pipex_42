#include "pipex.h"
int split_join(char **pwd, int i, char *s)
{
    while(pwd[++i])
        pwd[i] = ft_strjoin(pwd[i], "/");
    i = -1;
    while(pwd[++i])
        pwd[i] = ft_strjoin(pwd[i], s);
    i = -1;
    while(pwd[++i] != NULL)
    {

        if(access(pwd[i], F_OK) == 0)
            break;
    }
    return i;
}

char *check_path(char **envp, char *s)
{
    int i;
    char **pwd;
    char *path;

    i = -1;
    while (envp[++i] != NULL)
    {
        if(ft_strncmp(envp[i], "PATH", 4) == 0)
            break;
    }
    if (envp[i] == NULL)
    {
         return NULL;
    }
    path = &envp[i][5];
    pwd = ft_split(path,':');
    i= -1;
    i = split_join(pwd, i, s);
    if(pwd[i])
        path = ft_strdup(pwd[i]);
    else
        path = NULL;
    frealltab(pwd);
    free(pwd);
    return path;
}
