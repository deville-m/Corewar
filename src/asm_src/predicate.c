/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predicate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 12:02:05 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/04 15:02:45 by ctrouill         ###   ########.fr       */
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

char			is_instruct(const char *line)
{
	uint8_t		i;
	uint16_t	j;

	i = 0;
	j = operator_tsize();
	while (i <= j)
	{
		if (ft_strequ(line, g_op_tab[i].name))
			return (g_op_tab[i].op_code);
		i++;
	}
	return (0);
}

/*
** @desc predicate to check if
**       the line is strictly
**       composed of space/tabs
**       nor empty.
** @params line to test
** @return bolean :: t_bool
*/

t_bool			is_empty(const char *line)
{
	uint32_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!ft_isblank(line[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
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

char			is_params_ok(const char opcode,
							const char *params,
							t_bool *status)
{
	char		**sp;
	char		ret = 0;

	if (P_OUTRANGE(opcode, operator_tsize()) || params == NULL
		|| (sp = ft_strsplit(params, SEPARATOR_CHAR)) == NULL
		|| arguments_size((const char**)sp) != g_op_tab[(int)opcode].nb_param)
		return (!((*status = FALSE) || 1));
	return (ret);
}
