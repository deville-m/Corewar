/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 19:55:57 by mdeville          #+#    #+#             */
/*   Updated: 2018/06/01 18:01:36 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"
#include "ft_ctype.h"
#include "ft_string.h"

/*
** @desc predicate for comments
** @params arg current curs
** @return boolean
*/

size_t		is_comment(const char *arg)
{
	size_t len;

	len = ft_strlen((char*)COMMENT_CMD_STRING);
	if (!ft_strnequ(COMMENT_CMD_STRING, arg, len))
		return (0);
	return (len);
}

/*
** @desc predicate for name
** @params arg current curs
** @return boolean
*/

size_t		is_name(const char *arg)
{
	size_t len;

	len = ft_strlen((char*)NAME_CMD_STRING);
	if (!ft_strnequ(NAME_CMD_STRING, arg, len))
		return (0);
	return (len);
}

/*
** @desc predicate for ilabels
** @params arg current curs
** @return boolean
*/

size_t		is_indirect_label(const char *arg)
{
	size_t i;

	i = 0;
	if (arg[i] != LABEL_CHAR)
		return (0);
	i++;
	while (arg[i] && ft_strchr(LABEL_CHARS, arg[i]))
		++i;
	if (i >= 2)
		return (i);
	return (0);
}

/*
** @desc predicate for dlabels
** @params arg current curs
** @return boolean
*/

size_t		is_direct_label(const char *arg)
{
	size_t tmp;

	if (*arg != DIRECT_CHAR)
		return (0);
	tmp = is_indirect_label(arg + 1);
	if (tmp)
		return (1 + tmp);
	else
		return (0);
}

/*
** @desc predicate for string typep
** @params arg current curs
** @return boolean
*/

size_t		is_string(const char *arg)
{
	size_t	i;

	if (arg[0] != STRING_CHAR)
		return (0);
	i = 1;
	while (arg[i] && arg[i] != STRING_CHAR)
		++i;
	if (arg[i] != STRING_CHAR)
		return (0);
	return (i + 1);
}

/*
** @desc predicate for instructions
** @params arg current curs
** @return boolean
*/

size_t		is_instruction(const char *arg)
{
	size_t i;

	i = 0;
	while (arg[i] && ft_strchr(LABEL_CHARS, arg[i]))
		++i;
	if (!arg[i] || ft_strchr(WHITESPACE, arg[i]))
		return (i);
	return (0);
}
