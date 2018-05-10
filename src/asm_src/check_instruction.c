/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 23:16:06 by mdeville          #+#    #+#             */
/*   Updated: 2018/05/10 23:35:46 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "dlst.h"
#include "ft_string.h"

t_dlist		*check_instruction(t_dlist *lst)
{
	size_t	i;

	i = 0;
	while (i < INSTRUCTION_NBR
			&& !ft_strequ(get_token(lst)->raw, g_op_tab[i].name))
		++i;
	if (i == INSTRUCTION_NBR)
		syntax_error("Unknown instruction at token", get_token(lst));

	return (lst);
}
