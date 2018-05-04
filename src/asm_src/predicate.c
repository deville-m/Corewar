/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predicate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 12:02:05 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/04 13:35:03 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>
#include <op.h>
#include <libft.h>
#include <stdint.h>

/*
** @desc Return associated opcode
**       of the line as char
** @params line current line cursor
** @return Success[Char != 0] | Failure[0]
*/

char		is_instruct(const char *line)
{
	uint8_t	i;

	i = 0;
	while (i <= REG_NUMBER)
	{
		if (ft_strequ(line, g_op_tab[i].name))
			return (g_op_tab[i].op_code);
		i++;
	}
	return (0);
}

/*
** @desc Return encoded byte and
**       implicitly status code.
** @params opcode cursor
** @params params raw instruction
**         arguments.
** @params status implicit return code.
** @return Maybe[encoded char | status true]
**         | None[0 | status false]
*/

char		is_params_ok(const char opcode,
						 const char *params,
						 t_bool *status)
{
	char	**split;
	char	ret;

	if (P_OUTRANGE(opcode))
		return (!((*status = FALSE) || 1));
	(void)split;
	(void)ret;
	(void)params;
	return (2);
}
