/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 20:35:08 by mdeville          #+#    #+#             */
/*   Updated: 2018/05/05 01:30:30 by mdeville         ###   ########.fr       */
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

	if (!line)
		return (FALSE);
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

static int		parse_line(int fd, t_dlist **res, char *line, int line_nbr)
{
	char	**split;
	char	*concat;
	char	*tmp;

	concat = line;
	while (multiline_string(concat) && get_next_line(fd, &line) > 0)
	{
		free(concat);
		free(line);
		concat = tmp;
	}
	free(line);
	if (!concat || !(split = ft_strsplit_str(concat, WHITESPACE)))
		exit(42); // allocation error
	
}

t_dlist		*tokenize(int fd)
{
	t_dlist		*res;
	char		*line;
	char		*tmp;
	int			line_nbr;

	line = NULL;
	res = NULL;
	line_nbr = 1;
	while (get_next_line(fd, &line) > 0)
	{
		line_nbr += parse_line(fd, &res, line, line_nbr);
		free(line);
	}
	free(line);
	return (res);
}
