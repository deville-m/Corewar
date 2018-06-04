/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crafting_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:32:21 by rbaraud           #+#    #+#             */
/*   Updated: 2018/06/04 18:27:13 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "ft_string.h"

t_lab	*new_t_lab(char *name, intmax_t offset, intmax_t instr_offset)
{
	t_lab	*new;

	new = (t_lab *)malloc(sizeof(t_lab));
	if (!new)
		bug_err("Error with t_lab malloc.\n");
	new->name = name;
	new->offset = offset;
	new->instr_offset = instr_offset;
	return (new);
}

t_lab	*is_labelled(t_env *env, t_asm_token *tok)
{
	t_list	*tmp;
	t_lab	*elem;

	tmp = env->lab_h;
	while (tmp)
	{
		elem = (t_lab *)tmp->content;
		if (ft_strcmp(elem->name, tok->raw) == 0)
			return (elem);
		tmp = tmp->next;
	}
	return (NULL);
}

void	add_lab_elem(t_env *env, t_asm_token *tok, intmax_t offset)
{
	t_lab	*new;

	new = new_t_lab(tok->raw, offset, -1);
	ft_lstinsert(&(env->lab_h), (void *)new, sizeof(t_lab));
}
