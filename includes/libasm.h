#ifndef LIBASM_H
# define LIBASM_H

# include <stddef.h>
# include <unistd.h>

#define C_RESET   "\033[0m"
#define C_WHITE   "\033[1;37m"
#define C_BLUE    "\033[1;34m"
#define C_GREEN   "\033[1;32m"
#define C_RED     "\033[1;31m"
#define C_YELLOW  "\033[1;33m"
#define C_CYAN    "\033[1;36m"

ssize_t ft_read(int fd, void *buf, size_t count);
size_t  ft_strlen(const char *s);
int     ft_strcmp(const char *s1, const char *s2);
// ssize_t ft_write(int fd, const void *buf, size_t count);
// char    *ft_strcpy(char *dst, const char *src);
// char    *ft_strdup(const char *s);

#endif
