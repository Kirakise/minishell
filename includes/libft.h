#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

size_t				ft_strlen(const char *s);
int					ft_isspace(char c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(char *s1, char *s2, int n);
void				*ft_memmove(void *dst, const void *src, size_t len);
int					ft_strchr(char const c, char const *set);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin_space(char const *s1, char const *s2);
t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
int					ft_lst_getsize(t_list *lst);
int					ft_lstadd_back(t_list **lst, t_list *new1);
int					ft_lstdestroy(t_list **lst);
int					get_next_line(int fd, char **line);

#endif
