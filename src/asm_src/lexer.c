/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 16:06:01 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/09 10:55:02 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

size_t	is_separator(const char *arg)
{
	return (*arg == SEPARATOR_CHAR);
}

/*
** @desc predicate to detect
**       direct instructions
** @params arg current curs
** @return boolean
*/

size_t	is_direct(const char *arg)
{
	size_t i;

	i = 0;
	if (arg[i] != DIRECT_CHAR)
		return (0);
	++i;
	while (arg[i] && ft_strchr(BASE, arg[i]))
		++i;
	if (!arg[i] || ft_strchr(WHITESPACE, arg[i]))
		return (i);
	return (0);
}

/*
** @desc predicate to detect
**       indirect instructions
** @params arg current curs
** @return boolean
*/

t_bool		is_indirect(const char *arg)
{
	int i;

	i = 0;
	while (arg[i] && ft_strchr(BASE, arg[i]))
		++i;
	if (!arg[i] || ft_strchr(WHITESPACE, arg[i]))
		return (i);
	return (0);
}

/*
** @desc predicate to detect
**       labels procs
** @params arg current curs
** @return boolean
*/

t_bool		is_label(const char *arg)
{
	while (*arg && ft_strchr(LABEL_CHARS, *arg))
		++arg;
	if (*arg != LABEL_CHAR)
		return (FALSE);
	++arg;
	return (!*arg);
}

/*
** @desc predicate to detect
**       register instructions
** @params arg current curs
** @return boolean
*/

t_bool		is_register(const char *arg)
{
	if (*arg != REGISTER_CHAR)
		return (FALSE);
	++arg;
	while (*arg && ft_strchr(BASE, *arg))
		++arg;
	return (!*arg);
}
