/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 19:06:59 by mdeville          #+#    #+#             */
/*   Updated: 2018/05/14 14:12:59 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "ft_printf.h"
#include "dlst.h"

int		filter_token(t_dlist *elem)
{
	t_asm_token *token;

	token = (t_asm_token *)elem->content;
	if (token->type == SEPARATOR
		|| token->type == ENDLINE
		|| token->type == END)
		return (0);
	return (1);
}

void		del_token(void *content, size_t content_size)
{
	t_asm_token *token;

	if (!content)
		return ;
	(void)content_size;
	token = (t_asm_token *)content;
	if (token->type != ENDLINE && token->type != END)
		free(token->raw);
	free(token);
}

void		syntax_error(char *message, t_asm_token *token)
{
	static const char *token_enum[] = {
		[COMMAND_COMMENT] = "COMMAND_COMMENT",
		[COMMAND_NAME] = "COMMAND_NAME",
		[STRING] = "STRING",
		[LABEL] = "LABEL",
		[REGISTER] = "REGISTER",
		[DIRECT] = "DIRECT",
		[INDIRECT] = "INDIRECT",
		[DIRECT_LABEL] = "DIRECT_LABEL",
		[INDIRECT_LABEL] = "INDIRECT_LABEL",
		[SEPARATOR] = "SEPARATOR",
		[INSTRUCTION] = "INSTRUCTION",
		[ENDLINE] = "ENDLINE",
		[END] = "END",
	};

	if (token->type == ENDLINE)
		ft_fprintf(2, "%s [TOKEN][%.3d:%.3d] %s\n",
			message, token->line, token->column, token_enum[token->type]);
	else
		ft_fprintf(2, "%s [TOKEN][%.3d:%.3d] %s \"%s\"\n",
			message, token->line, token->column,
			token_enum[token->type], token->raw);
	exit(42);
}

t_asm_token	*get_token(t_dlist *elem)
{
	if (!elem)
		return (NULL);
	else
		return ((t_asm_token *)elem->content);
}

void	print_tokens(t_dlist *elem)
{
	t_asm_token *token;

	token = (t_asm_token *)elem->content;
	if (token->type == ENDLINE)
		ft_printf("type: ENDLINE\n");
	else if (token->type == END)
		ft_printf("type: END\n");
	else
		ft_printf("type: %d -- raw: %s -- data: %d -- option: %d\n",
				token->type, token->raw, token->data, token->option);
}
