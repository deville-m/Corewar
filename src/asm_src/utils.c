/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 14:35:52 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/14 18:14:51 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>
#include <libft.h>
#include <stdint.h>

t_bool			multiline_string(const char *line)
{
	t_bool state;

	if (!line)
		return (TRUE);
	state = FALSE;
	while (*line)
	{
		if (*line == COMMENT_CHAR && state == 0)
			return (FALSE);
		else if (*line == STRING_CHAR && state == 0)
			state = TRUE;
		else if (*line == STRING_CHAR && state == 1)
			state = FALSE;
		++line;
	}
	return (state);
}

void		update_token(t_asm_token *token)
{
	char *tmp;

	tmp = token->raw;
	while (*tmp)
	{
		if (*tmp == EOL)
		{
			++token->line;
			token->column = 1;
		}
		else
			++token->column;
		tmp++;
	}
}

/*
** @desc compute tab size
** @params args splitted arguments
** @return size of tabs
*/

uint8_t			arguments_size(const char **args)
{
	uint8_t		i;

	i = 0;
	while (args[i] != NULL)
		i++;
	return (i);
}

/*
** @desc compute size of operators
** @params nil
** @return len of op array
*/

uint16_t		operator_tsize(void)
{
	return (sizeof(g_op_tab) / sizeof(g_op_tab[0]));
}
