#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define MAX_INPUT_LENGTH 256 
#define MAX_USERNAME_LENGTH 100 
#define MAX_PASSWORD_LENGTH 100 
#define MAX_TRIES 3 

void	outline(void);
char	*strinput(char *str);
char	*ft_strcpy(char *dst, char *src);
int	ft_strcmp(char *s1, char *s2);
int	ft_strl(char *s);
int	login(void);


