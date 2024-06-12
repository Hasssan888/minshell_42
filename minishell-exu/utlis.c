#include "main.h"

size_t	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;

	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest == src)
		return ((void *)src);
	d = (char *)dest;
	s = (char *)src;
	while (n--)
	{
		*d = *s;
		s++;
		d++;
	}
	return (dest);
}

char	*ft_strdup(const char *str)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(str) + 1;
	new_str = malloc(sizeof(char) * len);
	if (new_str == NULL)
		return (NULL);
	ft_memcpy(new_str, str, len);
	return (new_str);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	len_s;
	size_t	len_sub;
	char	*substring;

	if (s == NULL)
		return (0);
	len_s = ft_strlen(s);
	if (start >= len_s)
		return (ft_strdup(""));
	if (len < len_s - start)
		len_sub = len;
	else
		len_sub = len_s - start;
	substring = (char *)malloc((len_sub + 1) * sizeof(char));
	if (substring != NULL)
	{
		ft_memcpy(substring, s + start, len_sub);
		substring[len_sub] = '\0';
	}
	return (substring);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}