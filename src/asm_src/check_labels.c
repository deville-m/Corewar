/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_labels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 17:02:21 by mdeville          #+#    #+#             */
/*   Updated: 2018/06/01 20:43:04 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "dlst.h"
#include "ft_string.h"

static int	find_label(t_dlist *tokens, t_asm_token *tmp)
{
	char		*to_find;
	size_t		len;
	t_asm_token	*tmp2;

	to_find = (tmp->type == DIRECT_LABEL) ? tmp->raw + 2 : tmp->raw + 1;
	len = ft_strlen(to_find);
	while (tokens)
	{
		tmp2 = get_token(tokens);
		if (tmp2->type == LABEL && ft_strnequ(to_find, tmp2->raw, len))
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

void		check_labels(t_dlist *tokens)
{
	t_dlist		*walk;
	t_asm_token	*tmp;

	walk = tokens;
	while (walk)
	{
		tmp = get_token(walk);
		if (tmp->type == DIRECT_LABEL || tmp->type == INDIRECT_LABEL)
		{
			if (!find_label(tokens, tmp))
				syntax_error(
						"Error while attempting to dereference label at token",
						tmp);
		}
		walk = walk->next;
	}
}
