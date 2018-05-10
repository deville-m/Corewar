/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 14:21:52 by mdeville          #+#    #+#             */
/*   Updated: 2018/05/10 23:42:49 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"
#include "dlst.h"
#include "lst.h"
#include "ft_printf.h"

static inline t_bool	check_header2(
									t_asm_token *next,
									t_bool status,
									t_dlist **lst)
{
	if (status || !next || next->type != STRING)
		syntax_error("Expecting string at token", next);
	*lst = (*lst)->next->next;
	return (TRUE);
}

static t_dlist	*check_header(t_dlist *tokens)
{
	t_bool		comment;
	t_bool		name;
	t_asm_token	*curr;
	t_asm_token	*next;

	comment = FALSE;
	name = FALSE;
	while ((curr = (t_asm_token *)tokens->content)->type == COMMAND_COMMENT
			|| curr->type == COMMAND_NAME || curr->type == ENDLINE)
	{
		next = (t_asm_token *)tokens->next->content;
		if (curr->type == COMMAND_COMMENT)
			comment = check_header2(next, comment, &tokens);
		else if (curr->type == COMMAND_NAME)
			name = check_header2(next, name, &tokens);
		else
			tokens = tokens->next;
	}
	if (!comment || !name)
		syntax_error("Syntax error at token", curr);
	return (tokens);
}

static t_dlist	*check_exec(t_dlist *tokens)
{
	t_asm_token	*curr;
	int			token_cpt;

	token_cpt = 0;
	while ((curr = (t_asm_token *)tokens->content)->type == LABEL
			|| curr->type == INSTRUCTION)
	{
		if (curr->type == LABEL)
		{
			tokens = tokens->next;
			if (((t_asm_token *)tokens->content)->type != INSTRUCTION
				|| ((t_asm_token *)tokens->content)->type != ENDLINE)
				syntax_error("Syntax error at token",
							(t_asm_token *)tokens->content);
			curr->raw[ft_strlen(curr->raw) - 1] = '\0';
		}
		else
			tokens = check_instruction(tokens);
		++token_cpt;
	}
	if (!token_cpt)
		syntax_error("Syntax error at token", curr);
	return (tokens);
}

void			syntax_check(t_dlist *tokens)
{
	tokens = check_header(tokens);
//	tokens = check_exec(tokens);
}
