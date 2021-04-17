#include "../../includes/minishell.h"
#include "../../includes/libft.h"

extern t_shell g_shell;

void cd(t_cmd *cmd)
{
    char *s;
    int error;

    if (!(cmd->args[1]) || !ft_strcmp(cmd->args[1], "~"))
    {
        error = chdir((s = find_var("HOME")));
        if (s && s[0] != 0)
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
            error = chdir(cmd->args[1]);
            if (error != 0)
            {
                s = strerror(errno);
                printf("%s\n", s);
            }
        }
}