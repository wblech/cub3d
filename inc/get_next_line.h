/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:20:11 by wbertoni          #+#    #+#             */
/*   Updated: 2020/06/02 11:52:25 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# define BUFFER_SIZE 128

# ifndef OPEN_MAX
#  define OPEN_MAX 1028
# endif
int					ft_strlen_char(const char *str, char c);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_haschr(const char *s, int c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					get_next_line(int fd, char **line);

#endif
