/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 14:21:52 by mdeville          #+#    #+#             */
/*   Updated: 2018/06/05 17:24:24 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"
#include "dlst.h"
#include "lst.h"
#include "ft_printf.h"

static inline int		check_header2(
									t_asm_token *next,
									int status,
									t_dlist **lst)
{
	size_t len;

	if (status)
		syntax_error("Command already present at token", get_token(*lst));
	if (!next || next->type != STRING)
		syntax_error("Expecting string at token", next);
	len = ft_strlen(next->raw);
	if (get_token(*lst)->type == COMMAND_NAME && len > PROG_NAME_LENGTH)
		syntax_error("Name too long at token", next);
	if (get_token(*lst)->type == COMMAND_COMMENT && len > COMMENT_LENGTH)
		syntax_error("Comment too long at token", next);
	*lst = (*lst)->next->next;
	return (1);
}

static t_dlist			*check_header(t_dlist *tokens)
{
	int					comment;
	int					name;
	t_asm_token			*curr;
	t_asm_token			*next;

	comment = 0;
	name = 0;
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

	check_labels(tokens);
	stop = check_header(tokens);
	stop = check_exec(stop);
	if (stop->prev)
		stop->prev->next = NULL;
	stop->prev = NULL;
	ft_dlstdel(&stop, del_token);
	ft_dlstfilter(&tokens, filter_token, del_token);
	return (tokens);
}
