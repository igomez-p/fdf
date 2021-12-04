/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 18:11:22 by igomez-p          #+#    #+#             */
/*   Updated: 2021/12/04 20:08:18 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE	32

void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
size_t				ft_strlen(const char *s);
int					ft_isdigit(int c);
int					ft_isprint(int c);
char				*ft_strchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
int					ft_atoi(const char *str);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(char *s1, char const *s2);
char				*ft_swap(char *l, char *buf);
//int					get_next_line(int fd, char **line, char **b, char **l);
int		get_next_line(int fd, char **line);

#endif
