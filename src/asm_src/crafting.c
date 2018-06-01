/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crafting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:50:51 by rbaraud           #+#    #+#             */
/*   Updated: 2018/06/01 18:45:59 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

unsigned char	craft_coding_byte(t_list *head)
{
	t_asm_token		*tmp;
	unsigned char	result;
	int				i;

	i = 2;
	result = 0;
	if (!head)
		return (0);
	tmp = (t_asm_token *)head->content;
	while (head && tmp && LABEL < tmp->type && tmp->type < SEPARATOR)
	{
		if (tmp->type == REGISTER)
			result |= REG_CODE;
		else if (tmp->type == DIRECT || tmp->type == DIRECT_LABEL)
			result |= DIR_CODE;
		else
			result |= IND_CODE;
		result <<= 2;
		i -= 1;
		head = head->next;
		tmp = (t_asm_token *)head->content;
	}
	while (i-- >= 0)
		result <<= 2;
	return (result);
}

int				craft_instru(t_env *env,
					t_list *current, int offset, int *in_off)
{
	t_asm_token		*tok;
	unsigned char	c;

	*in_off = offset;
	if (!current)
		bug_err("Error while trying to craft instruction\n");
	if (!(tok = (t_asm_token *)current->content))
		bug_err("Error while trying to craft instruction\n");
	offset += write(env->fd, &(tok->data), 1);
	if (tok->option)
	{
		if (!(c = craft_coding_byte(current->next)))
			bug_err("Error while crafting coding byte\n");
		offset += write(env->fd, &c, 1);
	}
	return (offset);
}

// ici je dois utiliser IND_SIZE & DIR_SIZE mais je n'ai pas
// la moindre idee de comment adapter cela aux short et int
int				craft_labels(t_env *env,
					t_asm_token *tok, int offset, int instr_offset)
{
	t_lab	*tmp;
	short	result;

	if ((tmp = is_labelled(env, tok)))
	{
		if (tok->type == DIRECT_LABEL && !tok->option)
			offset += write(env->fd, "\0\0", 2);
		result = (short)(tmp->offset - instr_offset);
		swap_endian(&(result), 2);
		offset += write(env->fd, &result, 2);
	}
	else
	{
		if (tok->type == DIRECT_LABEL && !tok->option)
			offset += write(env->fd, "\0\0", 2);
		tmp = new_t_lab(tok->raw, offset, instr_offset);
		ft_lstinsert(&(env->to_do), tmp, sizeof(t_lab));
		offset += write(env->fd, "aa", 2);
	}
	return (offset);
}

// meme probleme de modularite que ci-dessus
int				craft_values(t_env *env, t_asm_token *tok, int offset)
{
	short	tmp;

	tmp = 0;
	if (tok->option || tok->type == INDIRECT || tok->type == INDIRECT_LABEL)
	{
		tmp = (short)tok->data;
		swap_endian(&tmp, 2);
		offset += write(env->fd, &tmp, 2);
	}
	else
	{
		swap_endian(&(tok->data), 4);
		offset += write(env->fd, &(tok->data), 4);
	}
	return (offset);
}

int				craft_prog(t_env *env, t_list *tmp)
{
	t_asm_token		*tok;
	int				offset;
	int				instr_offset;

	offset = 0;
	instr_offset = offset;
	while (tmp)
	{
		tok = (t_asm_token *)tmp->content;
		if (tok->type == LABEL)
			add_lab_elem(env, tok, offset);
		else if (tok->type == INSTRUCTION)
			offset = craft_instru(env, tmp, offset, &instr_offset);
		else
		{
			if (tok->type == REGISTER)
				offset += write(env->fd, &(tok->data), 1);
			else if (tok->type == DIRECT_LABEL || tok->type == INDIRECT_LABEL)
				offset = craft_labels(env, tok, offset, instr_offset);
			else if (tok->type == DIRECT || tok->type == INDIRECT)
				offset = craft_values(env, tok, offset);
		}
		tmp = tmp->next;
	}
	return (offset);
}
