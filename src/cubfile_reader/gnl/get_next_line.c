/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 13:27:25 by wbertoni          #+#    #+#             */
/*   Updated: 2020/10/05 17:31:38 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			ft_readfile(int fd, char **remember)
{
	int			res;
	char		*buf;
	char		*tmp;

	tmp = remember[fd];
	if (remember[fd] == NULL)
		remember[fd] = ft_substr("", 0, 0);
	else
		remember[fd] = ft_substr(remember[fd], ft_strlen_char(remember[fd],
					'\n') + 1, ft_strlen_char(remember[fd], '\0'));
	free(tmp);
	if (!(buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	buf[0] = '\0';
	while (!(ft_haschr(buf, '\n')) && (res = read(fd, buf, BUFFER_SIZE)))
	{
		if (res == -1)
			return (-1);
		buf[res] = '\0';
		tmp = remember[fd];
		remember[fd] = ft_strjoin(remember[fd], buf);
		free(tmp);
	}
	free(buf);
	return (res);
}

int			get_return(int fd, int res, char **remember)
{
	if (res == -1)
		return (-1);
	if (res == 0)
	{
		if (ft_haschr(remember[fd], '\n'))
			return (1);
		else if (remember[fd][0] != '\0')
			return (1);
		else
		{
			if (remember[fd] != NULL)
			{
				free(remember[fd]);
				remember[fd] = NULL;
			}
			return (0);
		}
	}
	return (1);
}

int			get_next_line(int fd, char **line)
{
	static	char	*remember[OPEN_MAX];
	int				res;

	if (BUFFER_SIZE < 1 || fd < 0 || line == NULL)
		return (-1);
	res = ft_readfile(fd, remember);
	if (res == -1)
		return (-1);
	*line = ft_substr(remember[fd], 0, ft_strlen_char(remember[fd], '\n'));
	res = get_return(fd, res, remember);
	return (res);
}
