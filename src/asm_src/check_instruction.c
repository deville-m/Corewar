/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 23:16:06 by mdeville          #+#    #+#             */
/*   Updated: 2018/05/11 18:57:19 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "dlst.h"
#include "memory.h"
#include "ft_string.h"

static void		check_param(t_asm_token *curr, size_t offset, char *msg, t_op o)
{
	curr->data = ft_atoi_base(curr->raw + offset, BASE, WHITESPACE, MINUS);
	if (curr->type == REGISTER && curr->data <= 0)
		syntax_error(msg, curr);
	if ((curr->type == DIRECT || curr->type == DIRECT_LABEL) && o.index == 1)
		curr->option = 1;
	else
		curr->option = 0;
}

static void		check_parameter(t_asm_token *curr, t_op op, size_t param)
{
	if (curr->type == REGISTER && op.arg_type[param] & T_REG)
		check_param(curr, 1, "Invalid register at token", op);
	else if (curr->type == DIRECT && op.arg_type[param] & T_DIR)
		check_param(curr, 1, "Invalid direct at token", op);
	else if (curr->type == DIRECT_LABEL && op.arg_type[param] & T_DIR)
	{
		ft_memmove(curr->raw, curr->raw + 2, ft_strlen(curr->raw + 1));
		curr->option = op.index;
	}
	else if (curr->type == INDIRECT && op.arg_type[param] & T_IND)
		check_param(curr, 0, "Invalid indirect at token", op);
	else if (curr->type == INDIRECT_LABEL && op.arg_type[param] & T_IND)
		ft_memmove(curr->raw, curr->raw + 1, ft_strlen(curr->raw));
	else
	{
		ft_fprintf(2,
			"Invalid parameter %zu for instruction %s at token [%.3d:%.3d]\n",
			param, op.name, curr->line, curr->column);
		exit(42);
	}
}

static t_dlist	*check_parameters(t_dlist *lst, t_op op)
{
	int			param;
	t_asm_token	*curr;

	param = 0;
	while ((curr = get_token(lst))->type == DIRECT || curr->type == INDIRECT
			|| curr->type == DIRECT_LABEL || curr->type == INDIRECT_LABEL
			|| curr->type == REGISTER)
	{
		check_parameter(curr, op, param);
		lst = lst->next;
		if (get_token(lst)->type == SEPARATOR)
			lst = lst->next;
		++param;
	}
	if (param != op.nb_param)
	{
		ft_fprintf(2, "Invalid parameter %zu for instruction %s\n",
				param, op.name);
		exit(42);
	}
	return (lst);
}

t_dlist			*check_instruction(t_dlist *lst)
{
	size_t	i;

	i = 0;
	while (i < INSTRUCTION_NBR
			&& !ft_strequ(get_token(lst)->raw, g_op_tab[i].name))
		++i;
	if (i == INSTRUCTION_NBR)
		syntax_error("Unknown instruction at token", get_token(lst));
	get_token(lst)->option = g_op_tab[i].coding_byte;
	get_token(lst)->data = g_op_tab[i].op_code;
	lst = check_parameters(lst->next, g_op_tab[i]);
	if (get_token(lst)->type != ENDLINE)
		syntax_error("Syntax error at token", get_token(lst));
	return (lst);
}
