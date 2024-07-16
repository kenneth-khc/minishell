#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif
char	*get_next_line(int fd);
void	read_file(int fd, char **line, char **buffer);
void	extract_line(char **buffer, char **line, ssize_t *bytes);
void	*gnl_calloc(size_t count, size_t size);
char	*gnl_strchr(const char *str, int c);
char	*gnl_strjoin(char *str1, char const *str2);
char	*gnl_substr(char const *str, unsigned int index, size_t len);
int ft_strlen(const char *s);
#endif