#include "main.h"

char	*ft_read_creat(int fd, char *s)
{
	char	*buf;
	ssize_t	read_char;

	read_char = 1;
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	while (!ft_strchr(s, '\n') && read_char)
	{
		read_char = read(fd, buf, BUFFER_SIZE);
		if (read_char == -1)
		{
			free(buf);
			free(s);
			return (NULL);
		}
		buf[read_char] = '\0';
		s = ft_strjoin(s, buf);
	}
	free(buf);
	return (s);
}

char	*ft_extract_line(char *s)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!ft_strlen(s))
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		new_line = malloc(sizeof(char) * (i + 2));
	else
		new_line = malloc(sizeof(char) * (i + 1));
	if (!new_line)
		return (NULL);
	while (j <= i && s[j])
	{
		new_line[j] = s[j];
		j++;
	}
	new_line[j] = '\0';
	return (new_line);
}

char	*ft_return_s(char *s)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i] || s[i] == '\n')
	{
		free(s);
		return (NULL);
	}
	i++;
	new_str = malloc(sizeof(char) * (ft_strlen(s) - i + 1));
	if (!new_str)
	{
		free(s);
		return (NULL);
	}
	while (s[i])
		new_str[j++] = s[i++];
	new_str[j] = '\0';
	free(s);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*s;
	char		*line_next;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	s = ft_read_creat(fd, s);
	if (!s)
		return (NULL);
	line_next = ft_extract_line(s);
	s = ft_return_s(s);
	return (line_next);
}