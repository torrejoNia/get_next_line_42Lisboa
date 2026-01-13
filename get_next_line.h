/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnavarr <esnavarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 11:13:55 by esnavarr          #+#    #+#             */
/*   Updated: 2026/01/13 11:14:04 by esnavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

//	Value can be changed at compile time
//	by adding "-D BUFFER_SIZE=n" to the compiler call
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

//  	get_next_line.c
char	*get_next_line(int fd);

//  	get_next_line_utils.c
void	ft_bzero(void *s, size_t n);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);

#endif