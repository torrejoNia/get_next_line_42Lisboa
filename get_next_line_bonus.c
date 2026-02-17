/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnavarr <esnavarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 11:14:55 by esnavarr          #+#    #+#             */
/*   Updated: 2026/01/14 18:26:41 by esnavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	read_buffer(int fd, char **stash, char *buffer)
{
	char	*tmp;
	int		bytes;

	ft_bzero(buffer, BUFFER_SIZE + 1);
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes < 0 || buffer == NULL)
	{
		free(*stash);
		*stash = NULL;
		return (-1);
	}
	if (bytes == 0)
		return (bytes);
	tmp = ft_strjoin(*stash, buffer);
	free(*stash);
	*stash = tmp;
	return (bytes);
}

static void	remove_result(char **stash)
{
	char	*nl;
	char	*tmp;
	size_t	i;
	size_t	j;

	nl = ft_strchr(*stash, '\n');
	if (!nl)
	{
		free(*stash);
		*stash = NULL;
		return ;
	}
	tmp = malloc((ft_strlen(nl)) * sizeof(char));
	i = 0;
	j = ft_strlen(*stash) - ft_strlen(nl) + 1;
	while (j < ft_strlen(*stash))
		tmp[i++] = (*stash)[j++];
	tmp[i] = '\0';
	free(*stash);
	*stash = tmp;
	if (**stash == 0)
	{
		free(*stash);
		*stash = NULL;
	}
}

static void	get_result(char **stash, char **result)
{
	char	*nl;
	size_t	len;
	size_t	i;

	nl = ft_strchr(*stash, '\n');
	len = ft_strlen(*stash) - ft_strlen(nl) + 2;
	*result = (char *)malloc(len * sizeof(char));
	if (!*result)
		return ;
	i = 0;
	while (i < len - 1)
	{
		(*result)[i] = (*stash)[i];
		i++;
	}
	(*result)[i] = '\0';
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FILES_OPENED];
	char		*result;
	char		*buffer;
	int			bytes;

	if (fd < 0 || fd >= MAX_FILES_OPENED || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (ft_strchr(stash[fd], '\n') == NULL && bytes > 0)
		bytes = read_buffer(fd, &(stash[fd]), buffer);
	free(buffer);
	if (bytes == -1)
		return (NULL);
	if (ft_strlen(stash[fd]) == 0)
		return (NULL);
	get_result(&(stash[fd]), &result);
	remove_result(&(stash[fd]));
	return (result);
}

/*
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd1 = open("test.txt", O_RDONLY);
    int fd2 = open("test2.txt", O_RDONLY);
    char *line1;
    char *line2;

    if (fd1 < 0 || fd2 < 0)
    {
        perror("open failed");
        return 1;
    }

    // Read alternately from both files
    while (1)
    {
        line1 = get_next_line(fd1);
        line2 = get_next_line(fd2);

        if (!line1 && !line2)
            break; // both files finished

        if (line1)
        {
            printf("fd1: %s", line1);
            free(line1);
        }

        if (line2)
        {
            printf("fd2: %s", line2);
            free(line2);
        }
    }

    close(fd1);
    close(fd2);
    return 0;
} */