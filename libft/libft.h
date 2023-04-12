/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 19:09:52 by samy              #+#    #+#             */
/*   Updated: 2023/04/12 17:52:40 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 42

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_strcmp(const char *s1, const char *s2);
int					ft_atoi(const char *str);
int					ft_isalpha(char c);
int					ft_isdigit(char c);
int					ft_isalnum(char c);
int					ft_isascii(int c);
int					ft_isprint(int c);
size_t				ft_strlen(const char *s);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
void				*ft_memmove(void *dst, const void *src, size_t len);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s1);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
int					ft_strrncmp(const char *s1, const char *s2, size_t n);
int					ft_putchar(char c);
int					ft_putstr(char *s);
int					ft_putnbr(int n);
int					ft_putnbr_ul(unsigned long n);
int					put_hexa(unsigned long nb, char *base);
int					print_address(unsigned long nb);
int					print_hex(unsigned int nb, const char format);
int					ft_printf(const char *str, ...);
char				*get_next_line(int fd);
char				*ft_strjoin_gnl(char *s1, char *s2);
char				*ft_strchr(const char *s, int c);
char				*ft_free(char **str);
void				ft_free_split(char **split);
int					ft_nb_split(char **split);
#endif