/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crafting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:50:51 by rbaraud           #+#    #+#             */
/*   Updated: 2018/06/04 15:33:31 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>
#include <stdint.h>

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

intmax_t		craft_instru(t_env *env,
					t_list *current, intmax_t offset, intmax_t *in_off)
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

int				craft_labels(t_env *env,
					t_asm_token *tok, intmax_t offset, intmax_t instr_offset)
{
	t_lab			*tmp;
	unsigned char	result[IND_SIZE];
	intmax_t		i;

	i = 0;
	if ((tmp = is_labelled(env, tok)))
	{
		while (i++ < IND_SIZE && tok->type == DIRECT_LABEL && !tok->option)
			offset += write(env->fd, "\0", 1);
		i = tmp->offset - instr_offset;
		ft_memcpy(result, &i, IND_SIZE);
		swap_endian(&(result), IND_SIZE);
		offset += write(env->fd, &result, IND_SIZE);
	}
	else
	{
		while (i++ < IND_SIZE && tok->type == DIRECT_LABEL && !tok->option)
			offset += write(env->fd, "\0", 1);
		tmp = new_t_lab(tok->raw, offset, instr_offset);
		ft_lstinsert(&(env->to_do), tmp, sizeof(t_lab));
		i = 0;
		while (i++ < IND_SIZE)
			offset += write(env->fd, "a", 1);
	}
	return (offset);
}

intmax_t		craft_values(t_env *env, t_asm_token *tok, intmax_t offset)
{
	unsigned char	tmpind[IND_SIZE];
	unsigned char	tmpdir[DIR_SIZE];
	unsigned char	tmpreg[REG_SIZE];

	if (tok->option || tok->type == INDIRECT || tok->type == INDIRECT_LABEL)
	{
		ft_memcpy(tmpind, &(tok->data), IND_SIZE);
		swap_endian(tmpind, IND_SIZE);
		offset += write(env->fd, tmpind, IND_SIZE);
	}
	else if (tok->type == DIRECT || tok->type == DIRECT_LABEL)
	{
		ft_memcpy(tmpdir, &(tok->data), DIR_SIZE);
		swap_endian(tmpdir, DIR_SIZE);
		offset += write(env->fd, tmpdir, DIR_SIZE);
	}
	else
	{
		ft_memcpy(tmpreg, &(tok->data), REG_SIZE);
		swap_endian(tmpreg, REG_SIZE);
		offset += write(env->fd, tmpreg, REG_SIZE);
	}
	return (offset);
}

intmax_t		craft_prog(t_env *env, t_list *tmp)
{
	t_asm_token	*tok;
	intmax_t	offset;
	intmax_t	instr_offset;

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
