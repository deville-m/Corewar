/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 14:35:52 by ctrouill          #+#    #+#             */
/*   Updated: 2018/06/05 17:35:47 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>
#include <libft.h>
#include <stdint.h>

int				multiline_string(const char *line)
{
	int			state;

	if (!line)
		return (1);
	state = 0;
	while (*line)
	{
		if (ft_strchr(COMMENT_CHARS, *line) && state == 0)
			return (0);
		else if (*line == STRING_CHAR && state == 0)
			state = 1;
		else if (*line == STRING_CHAR && state == 1)
			state = 0;
		++line;
	}
	return (state);
}

void			update_token(t_asm_token *token)
{
	char		*tmp;

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
