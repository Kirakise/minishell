#include "../../includes/minishell.h"
#include "../../includes/libft.h"

extern t_shell g_shell;

void cd(t_cmd *cmd)
{
    char *s;
    int error;

    if (g_shell.pidt == 0)
        exit(0);
    if (!cmd->args[1] || !ft_strcmp(cmd->args[1], "~"))
    {
        error = chdir((s = find_var("HOME")));
        free(s);
        if (error != 0)
        {
            s = strerror(errno);
            printf("%s\n", s);
        }
    }
    else if (cmd->args[1][0] == '/')
    {
        error = chdir(cmd->args[1]);
        if (error != 0)
            {
                s = strerror(errno);
                printf("%s\n", s);
            }
    }
    else
        {
            s = ft_strjoin(find_var("PWD"), cmd->args[1]);
            error = chdir(s);
            free(s);
            if (error != 0)
            {
                s = strerror(errno);
                printf("%s\n", s);
            }
        }
}