/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 20:35:08 by mdeville          #+#    #+#             */
/*   Updated: 2018/06/05 17:35:18 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "op.h"
#include "ft_ctype.h"
#include "dlst.h"
#include "asm.h"
#include "ft_string.h"
#include "ft_printf.h"
#include "get_next_line.h"

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
		if (!concat)
			concat = tmp;
		else
		{
			concat = ft_strnjoin(3, concat, eol, tmp);
			free(tmp);
		}
	}
	if (!ret)
		free(tmp);
	*line = concat;
	return (ret);
}

static int	parse_asm_token2(char *input, t_asm_token *token)
{
	size_t ret;

	if ((ret = is_label(input)))
		token->type = LABEL;
	else if ((ret = is_register(input)))
		token->type = REGISTER;
	else if ((ret = is_comment(input)))
		token->type = COMMAND_COMMENT;
	else if ((ret = is_name(input)))
		token->type = COMMAND_NAME;
	else if ((ret = is_indirect_label(input)))
		token->type = INDIRECT_LABEL;
	else if ((ret = is_direct_label(input)))
		token->type = DIRECT_LABEL;
	else if ((ret = is_separator(input)))
		token->type = SEPARATOR;
	else if ((ret = is_instruction(input)))
		token->type = INSTRUCTION;
	else
		return (0);
	return (ret);
}

static char	*parse_asm_token(t_dlist **res, char *input, t_asm_token *token)
{
	size_t ret;

	if ((ret = is_string(input)))
		token->type = STRING;
	else if ((ret = is_direct(input)))
		token->type = DIRECT;
	else if ((ret = is_indirect(input)))
		token->type = INDIRECT;
	else if (!(ret = parse_asm_token2(input, token)))
	{
		ft_fprintf(
				2,
				"Lexical error at [%d:%d]\n",
				token->line, token->column);
		exit(42);
	}
	token->raw = ft_strndup(input, ret);
	ft_dlstprepend(res, ft_dlstnew(token, sizeof(t_asm_token)));
	update_token(token);
	return (input + ret);
}

static void	process_input(t_dlist **res, char *input, t_asm_token *token)
{
	token->column = 1;
	while (*input)
	{
		if (ft_strchr(COMMENT_CHARS, *input))
			break ;
		else if (!ft_strchr(WHITESPACE, *input))
			input = parse_asm_token(res, input, token);
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
	t_asm_token	token;

	input = NULL;
	res = NULL;
	token.line = 1;
	while (get_next_lines(fd, &input) > 0)
	{
		process_input(&res, input, &token);
		token.type = ENDLINE;
		ft_dlstprepend(&res, ft_dlstnew(&token, sizeof(token)));
		token.column = 1;
		++token.line;
		free(input);
	}
	token.type = END;
	token.raw = NULL;
	ft_dlstprepend(&res, ft_dlstnew(&token, sizeof(token)));
	ft_dlstreverse(&res);
	return (res);
}
