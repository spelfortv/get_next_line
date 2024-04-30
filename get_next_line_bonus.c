/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spelfort <spelfort@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 20:52:22 by spelfort          #+#    #+#             */
/*   Updated: 2024/04/28 20:52:26 by spelfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_delete(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

char	*tidy_up(char *storage)
{
	char	*new_storage;
	char	*ptr;
	int		len;

	ptr = ft_strchr(storage, '\n');
	if (!ptr)
		return (ft_delete(&storage));
	else
		len = (ptr - storage) + 1;
	if (!storage[len])
		return (ft_delete(&storage));
	new_storage = ft_substr(storage, len, ft_strlen(storage) - len);
	ft_delete(&storage);
	if (!new_storage)
		return (NULL);
	return (new_storage);
}

char	*fresh_line(char *storage)
{
	char	*line;
	char	*ptr;
	int		len;

	ptr = ft_strchr(storage, '\n');
	len = (ptr - storage) + 1;
	line = ft_substr(storage, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

char	*read_data(int fd, char *storage)
{
	int		ret;
	char	*buffer;

	ret = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_delete(&storage));
	buffer[0] = '\0';
	while (ret > 0 && !ft_strchr(buffer, '\n'))
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret > 0)
		{
			buffer[ret] = '\0';
			storage = ft_strjoin(storage, buffer);
		}
	}
	free(buffer);
	if (ret == -1)
		return (ft_delete(&storage));
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage[FOPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if ((storage[fd] && !ft_strchr(storage[fd], '\n')) || !storage[fd])
		storage[fd] = read_data(fd, storage[fd]);
	if (!storage[fd])
		return (NULL);
	line = fresh_line(storage[fd]);
	if (!line)
		return (ft_delete(&storage[fd]));
	storage[fd] = tidy_up(storage[fd]);
	return (line);
}
