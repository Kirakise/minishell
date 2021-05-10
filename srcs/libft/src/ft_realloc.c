#include "../../../includes/libft.h"

char *ft_realloc(char *s1, char *s2)
{
    int i;
    int j;
    char *ret;

    j = 0;
    i = ft_strlen(s1) + ft_strlen(s2) + 1;
    ret = malloc(i);
    i = 0;
    while (s1 && s1[i])
    {
        ret[i] = s1[i];
        i++;
    }
    while (s2 && s2[j])
    {
        ret[i] = s2[j];
        i++;
        j++;
    }
    free(s1);
    ret[i] = 0;
    return(ret);
}
