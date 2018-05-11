/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 14:21:52 by mdeville          #+#    #+#             */
/*   Updated: 2018/05/11 19:38:01 by mdeville         ###   ########.fr       */
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

static t_dlist			*check_header(t_dlist *tokens)
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

static inline t_dlist	*check_label(t_asm_token *curr, t_dlist *lst)
{
	if (((t_asm_token *)lst->content)->type != INSTRUCTION
		&& ((t_asm_token *)lst->content)->type != ENDLINE)
		syntax_error("Syntax error at token", get_token(lst));
	curr->raw[ft_strlen(curr->raw) - 1] = '\0';
	return (lst);
}

static t_dlist			*check_exec(t_dlist *tokens)
{
	t_asm_token	*curr;
	int			token_cpt;

	token_cpt = 0;
	while ((curr = (t_asm_token *)tokens->content)->type == LABEL
			|| curr->type == INSTRUCTION || curr->type == ENDLINE)
	{
		if (curr->type == LABEL)
			tokens = check_label(curr, tokens->next);
		else if (curr->type == INSTRUCTION)
			tokens = check_instruction(tokens);
		else
			tokens = tokens->next;
		++token_cpt;
	}
	if (!token_cpt)
		syntax_error("Syntax error at token", curr);
	return (tokens);
}

t_dlist					*syntax_check(t_dlist *tokens)
{
	t_dlist	*stop;

	stop = check_header(tokens);
	stop = check_exec(stop);
	if (stop->prev)
		stop->prev->next = NULL;
	stop->prev = NULL;
	ft_dlstdel(&stop, del_token);
	ft_dlstfilter(&tokens, filter_token, del_token);
	return (tokens);
}
