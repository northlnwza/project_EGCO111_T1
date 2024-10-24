#include "header.h"

int	ft_strl(char *s)
{
	int	i;

	i  = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}
	
char	*ft_strcpy(char *dst, char *src)
{	
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;	
	return (dst);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 != 0 && *s2 != 0)
	{
		if (*s1 - *s2 != 0)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

char	*strinput(char *str)
{
	int	i;
	int	ch;

	i = 0;
	ch = 0;
	while (ch != '\n' && i < MAX_INPUT_LENGTH - 1)
	{	
		ch = getchar();
		if (ch == '\n')
			continue;
		str[i] = ch;
		i++;
	}
	str[i] = 0;
	return (str);
}

