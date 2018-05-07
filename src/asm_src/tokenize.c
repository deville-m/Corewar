/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 20:35:08 by mdeville          #+#    #+#             */
/*   Updated: 2018/05/07 17:47:25 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "op.h"
#include "ft_ctype.h"
#include "dlst.h"
#include "asm.h"
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

static int	get_next_lines(int fd, char **line)
{
	int		ret;
	char	*concat;
	char	*tmp;
	char	eol[2];

	eol[0] = EOL;
	eol[1] = '\0';
	concat = NULL;
	while (multiline_string(concat) && (ret = get_next_line(fd, &tmp)) > 0)
	{
		concat = ft_strnjoin(3, concat, eol, tmp);
		free(tmp);
	}
	*line = concat;
	return (ret);
}

static char	*parse_token(t_dlist **res, char *input, t_asm_token *token)
{
	if (is_separator(input))
	{
		token.type = SEPARATOR;
		token.data = ft_strdup(",");
		++input;
	}
	else if (is_direct(input))

}

static void	process_input(t_dlist **res, char *input, t_asm_token *token)
{
	token->column = 1;
	while (*input)
	{
		if (*input == EOL || *input == COMMENT_CHAR)
		{
			while (*input && *input != EOL)
				++input;
			token->type = ENDLINE;
			ft_dlstprepend(res, ft_dlstnew(token, sizeof(*token)));
			++token->line;
			token->column = 1;
			++input;
		}
		else if (!ft_strchr(WHITESPACE, *input))
			input = parse_token(res, input, token);
		else
		{
			++token->column;
			++input;
		}
	}
}

t_dlist		*tokenize(int fd)
{
	t_dlist		*res;
	char		*input;
	char		*tmp;
	t_asm_token	token;

	input = NULL;
	res = NULL;
	token.line = 1;
	while (get_next_lines(fd, &input) > 0)
	{
		process_input(&res, input, &token);
		token.type = ENDLINE;
		token.column = 1;
		++token.line;
		ft_dlstprepend(&res, ft_dlstnew(&token, sizeof(token)));
		free(input);
	}
	return (res);
}
