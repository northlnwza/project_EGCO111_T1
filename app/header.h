#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include <sys/stat.h>

#define PowerRate 4
#define MAX_INPUT_LENGTH 256 
#define MAX_USERNAME_LENGTH 100 
#define MAX_PASSWORD_LENGTH 100 
#define MAX_TRIES 3 
#define CLEAR_CMD "clear"
#define	KEEP_USERS "users.txt"
#define USERS_DIR "users_data"

void	editDevice(const char *username);
void	addDevice(const char *username);
void	viewDevice(const char *username);
void	deleteDevice(const char *username);
void	toregister(void);
void	lobby(void);
void	outline(char *current_user);
void	clearScreen();
char	*strinput(char *str);
char	*ft_strcpy(char *dst, char *src);
int	ft_strcmp(char *s1, char *s2);
int	ft_strl(char *s);
int	login(void);
int	electric(const char *username);
int	ft_atoi(char *str);
int	usedevice(const char *username);


