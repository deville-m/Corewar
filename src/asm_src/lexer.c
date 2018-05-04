/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 16:06:01 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/04 16:50:31 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>
#include <libft.h>

/*
** @desc predicate to detect
**       direct instructions
** @params arg current curs
** @return boolean
*/

t_bool		is_direct(const char *arg)
{
	size_t	i;

	i = 0;
	if (arg[i] == DIRECT_CHAR)
	{
		i++;
		while (arg[i] != '\0' && ft_isalnum(arg[i]))
			i++;
	}
	return (i == ft_strlen(arg));
}

/*
** @desc predicate to detect
**       indirect instructions
** @params arg current curs
** @return boolean
*/

t_bool		is_indirect(const char *arg)
{
	size_t	i;
	size_t	j;
	char	*base;

	i = 0;
	base = (char*)BASE;
	while (arg[i] != '\0')
	{
		j = 0;
		while (base[j] != '\0')
		{
			if (arg[i] != base[j])
				return (FALSE);
			j++;
		}
		i++;
	}
	return (i == ft_strlen(arg));
}

/*
** @desc predicate to detect
**       labels procs
** @params arg current curs
** @return boolean
*/

t_bool		is_label(const char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i + 1] == '\0')
			if (arg[i] != LABEL_CHAR)
				return (FALSE);
		i++;
	}
	return (TRUE);
}

/*
** @desc predicate to detect
**       register instructions
** @params arg current curs
** @return boolean
*/

t_bool		is_register(const char *arg)
{
	if (is_label(arg) || is_direct(arg))
		return (FALSE);
	if (arg[0] != 'r')
		return (FALSE);
	return (TRUE);
}
