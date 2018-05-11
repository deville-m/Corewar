/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 16:06:01 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/11 20:03:25 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

/*
** @desc predicate to detect
**       separators
** @params arg current curs
** @return boolean
*/

size_t		is_separator(const char *arg)
{
	return (*arg == SEPARATOR_CHAR);
}

/*
** @desc predicate to detect
**       direct instructions
** @params arg current curs
** @return boolean
*/

size_t		is_direct(const char *arg)
{
	size_t i;

	if (*arg != DIRECT_CHAR)
		return (0);
	i = is_indirect(arg + 1);
	if (i)
		return (1 + i);
	return (0);
}

/*
** @desc predicate to detect
**       indirect instructions
** @params arg current curs
** @return boolean
*/

size_t		is_indirect(const char *arg)
{
	int i;

	i = 0;
	if (arg[i] == MINUS)
		i++;
	while (arg[i] && ft_strchr(BASE, arg[i]))
		++i;
	if (((arg[0] != MINUS && i >= 1) || (arg[0] == MINUS && i >= 2))
		&& (!arg[i]
			|| ft_strchr(WHITESPACE, arg[i])
			|| arg[i] == SEPARATOR_CHAR))
		return (i);
	return (0);
}

/*
** @desc predicate to detect
**       labels procs
** @params arg current curs
** @return boolean
*/

size_t		is_label(const char *arg)
{
	size_t  i;

	i = 0;
	while (arg[i] && ft_strchr(LABEL_CHARS, arg[i]))
		++i;
	if (arg[i] != LABEL_CHAR)
		return (0);
	else
		return (i + 1);
}

/*
** @desc predicate to detect
**       register instructions
** @params arg current curs
** @return boolean
*/

size_t		is_register(const char *arg)
{
	size_t i;

	i = 0;
	if (arg[i] != REGISTER_CHAR)
		return (0);
	++i;
	while (arg[i] && ft_strchr(BASE, arg[i]))
		++i;
	if (i >= 2
		&& (!arg[i]
			|| ft_strchr(WHITESPACE, arg[i])
			|| arg[i] == SEPARATOR_CHAR))
		return (i);
	return (0);
}
