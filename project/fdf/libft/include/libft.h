/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 00:02:12 by alex              #+#    #+#             */
/*   Updated: 2021/08/01 00:57:28 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# define BUFFER_SIZE 4096

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}t_list;

typedef struct s_btree
{
	void			*item;
	struct s_btree	*left;
	struct s_btree	*right;
}t_btree;

/*
**	CTYPES
*/
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isdigit(int c);
int		ft_isspace(int c);

/*
**	BTREE
*/
t_btree	*btree_create_node(void *item);
int		btree_level_count(t_btree *root);
void	btree_apply_suffix(t_btree *root, void (*f)(void *item));
void	btree_apply_infix(t_btree *root, void (*f)(void *item));
void	btree_apply_prefix(t_btree *root, void (*f)(void *item));
void	btree_apply_by_lvl(t_btree *root, void (*f)(void *item, int i, int j));

/*
**	LIST
*/
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));

/*
**	STDLIB
*/
int		ft_atoi(const char *ptr);
void	*ft_calloc(size_t count, size_t size);

/*
**	WRITE
*/
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

/*
**	STRING
*/
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
void	ft_bzero(void *s, size_t n);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
void	*ft_memset(void *s, int c, size_t len);
char	*ft_strcat(char *dst, const char *src);
char	*ft_strndup(const char *s, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strncat(char *dst, const char *src, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *s1, const char *s2, size_t len);

/*
**	BSD
*/
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

/*
**	UTILS
*/
char	*ft_itoa(int n);
char	**ft_split(const char *s, char c);
int		get_next_line(int fd, char **line);
int		ft_atoi_base(char *str, char *base);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(const char *s, unsigned int start, size_t len);
#endif
