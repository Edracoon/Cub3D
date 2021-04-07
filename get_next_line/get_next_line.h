/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:25:23 by marvin            #+#    #+#             */
/*   Updated: 2021/04/07 12:31:44 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 999

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

char		*ft_stringjoin(char const *s1, char const *s2);
char		*ft_strdupl(char *src);
char		*ft_strcherche(const char *s, int c);
char		*ft_sousstr(char const *s, unsigned int start, size_t len);
char		*ft_strnew(size_t size);
int			ft_strfree(char **ptr);
int			get_next_line(int fd, char **line);
int			ft_slen2(const char *str);
char		*ft_memalloc(size_t size);
void		*ft_memoryset(void *b, int c, size_t len);
char		*verif_ret(char *str, int ret);
int			ft_tern(int a, int fals, int part, char **str);

#endif
