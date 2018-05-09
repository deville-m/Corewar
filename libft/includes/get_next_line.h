/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 20:24:11 by mdeville          #+#    #+#             */
/*   Updated: 2018/05/04 18:35:36 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../../include/op.h"
# include <unistd.h>
# define BUFF_SIZE 32
# ifndef EOL
#  define EOL '\n'
# endif

typedef struct		s_clist
{
	int				fd;
	int				offset;
	char			buff[BUFF_SIZE + 1];
	struct s_clist	*next;
}					t_clist;

int					get_next_line(const int fd, char **line);

#endif
