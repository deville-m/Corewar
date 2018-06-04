/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 14:46:05 by mdeville          #+#    #+#             */
/*   Updated: 2018/06/04 14:47:03 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

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
