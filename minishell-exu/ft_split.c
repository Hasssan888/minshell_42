#include "main.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*result;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = (char *)malloc(sizeof(char) * len);
	if (result != NULL)
	{
		ft_memcpy(result, s1, ft_strlen(s1));
		ft_memcpy(result + ft_strlen(s1), s2, ft_strlen(s2));
		result[len - 1] = '\0';
	}
	return (result);
}

static char	**ft_free(char **s, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

static int	count_w(char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str)
			count++;
		while (*str && *str != c)
			str++;
	}
	return (count);
}

static char	*alloc_w(char *str, char c)
{
	int		len_w;
	int		i;
	char	*ptr;

	len_w = 0;
	while (str[len_w] && str[len_w] != c)
		len_w++;
	ptr = (char *)malloc(sizeof(char) * (len_w + 1));
	if (ptr != NULL)
	{
		i = 0;
		while (i < len_w)
		{
			ptr[i] = str[i];
			i++;
		}
		ptr[i] = '\0';
	}
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		i;

	strs = (char **)malloc(sizeof(char *) * (count_w((char *)s, c) + 1));
	if (strs != NULL)
	{
		i = 0;
		while (*s)
		{
			if (*s != c)
			{
				strs[i] = alloc_w((char *)s, c);
				if (strs[i] == NULL)
					return (ft_free(strs, i));
				i++;
				while (*s && *s != c)
					s++;
			}
			else
				s++;
		}
		strs[i] = NULL;
	}
	return (strs);
}