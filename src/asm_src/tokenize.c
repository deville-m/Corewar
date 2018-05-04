/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 20:35:08 by mdeville          #+#    #+#             */
/*   Updated: 2018/05/04 21:04:15 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "op.h"
#include "ft_ctype.h"
#include "dlst.h"
#include "ft_string.h"
#include "get_next_line.h"

static t_bool	multiline_string(const char *line)
{
	t_bool state;

	state = FALSE;
	while (*line)
	{
		if (*line == COMMENT_CHAR && state == 0)
			return (FALSE);
		else if (*line == STRING_CHAR && state == 0)
			state = TRUE;
		else if (*line == STRING_CHAR && state == 1)
			state = FALSE;
		++line;
	}
	return (state);
}

static int		parse_line(t_dlist **res, const char *line, int line_nbr)
{
	char *tmp;

}

t_dlist		*tokenize(int fd)
{
	t_dlist		*res;
	char		*line;
	char		*tmp;
	int			line_nbr;

	res = NULL;
	line_nbr = 1;
	while (get_next_line(fd, &line) > 0)
	{
		line_nbr += parse_line(&res, line, line_nbr);
		free(line);
	}
	return (res);
}
