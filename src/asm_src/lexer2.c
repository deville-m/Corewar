/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 19:55:57 by mdeville          #+#    #+#             */
/*   Updated: 2018/05/04 20:16:23 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "ft_ctype.h"
#include "ft_string.h"

t_bool		is_comment(const char *arg)
{
	return (ft_strequ(COMMENT_CMD_STRING, arg));
}

t_bool		is_name(const char *arg)
{
	return (ft_strequ(NAME_CMD_STRING, arg));
}

t_bool		is_indirect_label(const char *arg)
{
	if (*arg != LABEL_CHAR)
		return (FALSE);
	while (*arg && ft_strchr(LABEL_CHARS, *arg))
		++arg;
	return (!*arg);
}

t_bool		is_direct_label(const char *arg)
{
	if (*arg != DIRECT_CHAR)
		return (FALSE);
	return (is_indirect_label(arg + 1));
}

t_bool		is_string(const char *arg)
{
	if (*arg != STRING_CHAR)
		return (FALSE);
	++arg;
	while (*arg && *arg != STRING_CHAR)
		++arg;
	return (*arg == STRING_CHAR);
}
