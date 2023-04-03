/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:53:23 by sde-smed          #+#    #+#             */
/*   Updated: 2022/12/20 15:04:59 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <limits.h>

static char	*set_result(char *src)
{
	char	*dest;
	size_t	i;
	size_t	j;

	if (!src)
		return (0);
	i = 0;
	while (src[i] && src[i] != '\n')
		i++;
	if (src[i] && src[i] == '\n')
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (0);
	j = 0;
	while (j < i)
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

static char	*set_str(char *str)
{
	char	*dest;
	size_t	i;
	size_t	j;

	i = 0;
	if (!str)
		return (ft_free(&str));
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] && str[i] == '\n')
		i++;
	j = 0;
	if (!str[i])
		return (ft_free(&str));
	while (str[i + j])
		j++;
	dest = malloc(sizeof(char) * (j + 1));
	if (!dest)
		return (ft_free(&str));
	j = 0;
	while (++j && str[i + j - 1])
		dest[j - 1] = str[i + j - 1];
	dest[j - 1] = '\0';
	free(str);
	return (dest);
}

static char	*read_fd(int fd, char *str)
{
	char	buffer[BUFFER_SIZE + 1];
	int		nb_read;

	nb_read = 1;
	while (!ft_strchr(str, '\n') && nb_read != 0)
	{
		nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read == -1)
			return (ft_free(&str));
		if (nb_read == 0)
			return (str);
		buffer[nb_read] = 0;
		str = ft_strjoin_gnl(str, buffer);
		if (!str)
			return (NULL);
	}
	return (str);
}

char	*get_next_linee(int fd)
{
	static char	*strs[OPEN_MAX];
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (NULL);
	if (read(fd, 0, 0) < 0)
		return (ft_free(&strs[fd]));
	strs[fd] = read_fd(fd, strs[fd]);
	if (!strs[fd])
		return (ft_free(&strs[fd]));
	result = set_result(strs[fd]);
	if (!result)
		return (ft_free(&strs[fd]));
	strs[fd] = set_str(strs[fd]);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (0);
	buffer[fd] = read_fd(fd, buffer[fd]);
	line = set_result(buffer[fd]);
	if (!line)
		return (ft_free(&buffer[fd]));
	buffer[fd] = set_str(buffer[fd]);
	return (line);
}
