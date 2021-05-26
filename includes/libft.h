#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_2list
{
	void			*content;
	struct s_2list	*prev;
	struct s_2list	*next;
}				t_2list;

size_t				ft_strlen(const char *s);
void				ft_putstr(const char *s);
void				ft_putstr_nl(const char *s);
int					ft_isspace(char c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(char *s1, char *s2, int n);
void				ft_bzero(char *s, int size);
void				*ft_calloc(size_t count, size_t size);
void				*ft_memmove(void *dst, const void *src, size_t len);
int					ft_strchr(char const c, char const *set);
void				ft_realloc(char **s1, char *s2);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin_3(char const *s1, char const *s2,
						char const *s3);
char				*ft_strjoin_space(char const *s1, char const *s2);
char				**ft_split(char const *str, char c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_itoa(int n);
int					ft_atoi(const char *str);

/* Lists */
t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
int					ft_lst_getsize(t_list *lst);
int					ft_lstadd_back(t_list **lst, t_list *new);
int					ft_lstdestroy(t_list **lst);
void				**lst_to_arr(t_list *lst);
t_2list				*tlist_new(void *content);
void				tlist_add_front(t_2list **lst, t_2list *new);
int					tlist_destroy(t_2list **lst);

#endif
