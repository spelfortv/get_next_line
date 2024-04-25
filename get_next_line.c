/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spelfort <spelfort@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:09:17 by spelfort          #+#    #+#             */
/*   Updated: 2024/02/14 18:09:24 by spelfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_file(int fd, char *txt_saved)
{
	char	*buffer;
	int		bytes;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(txt_saved, '\n') && bytes != 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			free(txt_saved);
			return (NULL);
		}
		buffer[bytes] = '\0';
		txt_saved = ft_strjoin(txt_saved, buffer);
	}
	free(buffer);
	return (txt_saved);
}

char	*ft_buffer_to_line(char *txt_saved)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (txt_saved[i] != '\0' && txt_saved[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = txt_saved[j];
		j++;
	}
	if (txt_saved[j] == '\n')
	{
		line[j] = txt_saved[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*ft_st_save(char *st_save)
{
	int		c;
	int		w;
	char	*s;

	c = 0;
	while (st_save[c] && st_save[c] != '\n')
		c++;
	if (!st_save[c])
	{
		free(st_save);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * ft_strlen(st_save) - c + 1);
	if (!s)
		return (NULL);
	c++;
	w = 0;
	while (st_save[c])
		s[w++] = st_save[c++];
	s[w] = '\0';
	free(st_save);
	return (s);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*txt_saved;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	txt_saved = ft_read_file(fd, txt_saved);
	if (!txt_saved)
		return (NULL);
	line = ft_buffer_to_line(txt_saved);
	txt_saved = ft_st_save(txt_saved);
	if (!line || !*line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
