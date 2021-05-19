#include "../../includes/minishell.h"
#include "../../includes/libft.h"

void insert(char **s, char *ins, int i, int j)
{
    char *tmp1;
    char *tmp2;

    tmp1 = ft_calloc(i, 1);
    tmp2 = ft_calloc(ft_strlen(*s) - j + 1, 1);
    ft_memmove(tmp1, *s, i);
    ft_memmove(tmp2, *s + j, ft_strlen(*s) - j);
    free(*s);
    *s = ft_strjoin_3(tmp1, ins, tmp2);
    free(tmp1);
    free(tmp2);
    free(ins);
}

int isvalid(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
        return (1);
    else
        return (0);
}

char *parsestr(char *s, int i, int j)
{
    char *tmp;

    tmp = ft_calloc(j - i + 2, 1);
    while (j > i)
    {
        tmp[j - i - 1] = s[j];
        j--;
    }
    return (tmp);
}

void parsevars(char **s)
{
    int i;
    int j;
    char *tmp;
    char *tmp2;

    i = 0;
    while ((*s)[i])
    {
        while ((*s)[i] && (*s)[i] != '$')
            i++;
        if ((*s)[i] == '\0')
            break;
        j = i + 1;
        while (isvalid((*s)[j]))
            j++;
        tmp = parsestr(*s, i, j);
        tmp2 = find_var(tmp);
        free(tmp);
        insert(s, tmp2, i, j);
        i++;
    }
}