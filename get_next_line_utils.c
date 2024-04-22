#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dsize)
{
	size_t	ssize;
	size_t	i;

	i = 0;
	ssize = ft_strlen(src);
	if (dsize != 0)
	{
		dsize--;
		while (src[i] != '\0' && dsize > 0)
		{
			dst[i] = src[i];
			dsize--;
			i++;
		}
		dst[i] = '\0';
	}
	return (ssize);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*str;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s2) + ft_strlen(s1);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	ft_strlcpy(str, s1, len + 1);
	ft_strlcat(str, s2, len + 1);
	return (str);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != (unsigned char) c)
	{
		if (str[i] == '\0')
			return (0);
		i++;
	}
	return ((char *)&str[i]);
}
