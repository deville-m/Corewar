/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 13:38:11 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/07 17:47:19 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

/*
** @desc transpose params
** @params occur current args cursor
** @return Nil[]
*/

void		transpose(t_tok *transpose,
				const char **split,
				char opcode,
				uint8_t i)
{
	if (split == NULL || *split == NULL)
		return ;
	while (i <= g_op_tab[(int)opcode].nb_param)
	{
		if (split[i] == NULL)
			return ;
		transpose[i] = tokenize(split[i]);
		i++;
	}
}

/*
** @desc tokenize params types
** @params occur current args cursor
** @return Maybe[Token] | Some[Sentinel]
*/

t_tok		tokenize(const char *occur)
{
	if (is_direct(occur))
		return (DIR);
	else if (is_indirect(occur))
		return (IND);
	else if (is_register(occur))
		return (REG);
	else if (is_label(occur))
		return (LAB);
	else
		return (SENTINEL);
}

/*
** @desc Verify type rules from
**       the params `arg_type`
** @params opcode opcode cursor
** @params split splited list
**         of the arguments
** @return boolean/success
*/

t_bool		check_rules(const char opcode,
					t_tok *transpose,
					uint8_t i)
{
	while (i < g_op_tab[(int)opcode].nb_param)
	{
		if (transpose[i] == SENTINEL)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
