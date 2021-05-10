#include "../../includes/minishell.h"
#include "../../includes/libft.h"
extern t_shell g_shell;

int ft_putchar(int s)
{
    return (write(g_shell.fd_1, &s, 1));
}
int ft_putint(int a)
{
    return (write(g_shell.fd_1, &a, 4));
}

int delete_last(char *s)
{
    int i;

    i = 0;
    if (!s || !s[i])
        return (-1);
    while (s[i])
        i++;
    s[i - 1] = 0;
    return (1);
}

char *tmpread()
{
    int l;
    char *str;
    char *s;

    s = calloc(1, 1);
    tputs(save_cursor, 1, ft_putchar);
    do
        {
            str = calloc(100, 1);
            l = read(g_shell.tmp_fd_0, str, 5);
            if (!strcmp(str, "\e[A"))
            {
                tputs(restore_cursor, g_shell.tmp_fd_1, ft_putchar);
                tputs(tigetstr("ed"), 1, ft_putchar); //Тут тебе надо напечатать в stdout предыдущий элемент истории и также поместить его в s
                write(g_shell.tmp_fd_1, "previous", 8);
                ft_bzero(str, l);
            }
            else if (!strcmp(str, "\e[B"))
            {
                tputs(restore_cursor, g_shell.tmp_fd_1, ft_putchar);
                tputs(tigetstr("ed"), 1, ft_putchar);
                write(g_shell.tmp_fd_1, "next", 4); //Тут тебе надо напечатать в stdout следующий элемент истории и также поместить его в s
                ft_bzero(str, l);
            }
            else if (!strcmp(str, "\x7f"))
            {
                if (delete_last(s) == 1)
                {
                    tputs(cursor_left, 1, ft_putchar);
                    tputs(delete_character, 1, ft_putchar);
                    ft_bzero(str, l);
                }
            }
            else if (strcmp(str, "\e[C") && strcmp(str, "\e[D") && strcmp(str, "\n") && strcmp(str, "\4"))
            {
                write(1, str, l);
                s = ft_realloc(s, str);
                ft_bzero(str, l);
            }
            free(str);
        } while (strcmp(str, "\n") && strcmp(str, "\4"));
    write(1, "\n", 1);
    return s;
}
