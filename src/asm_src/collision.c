/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 17:14:33 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/08 09:54:25 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

/*
** @desc assert if labels datas
**       is pure.
** @params i iterators
** @return Bool[Success];
*/

static t_bool	labels_check(const char *labels,
					uint_fast32_t i)
{
	while (labels[i] != '\0')
	{
		if (labels[i] == LABEL_CHAR
			|| labels[i] == COMMENT_CHAR
			|| labels[i] == DIRECT_CHAR
			|| labels[i] == SEPARATOR_CHAR)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/*
** @desc assert if labels datas
**       is pure.
** @params i iterators
** @return Bool[Success];
*/

static t_bool	base_check(const char *base,
					uint_fast32_t i)
{
	while (base[i] != '\0')
	{
		if (base[i] == LABEL_CHAR || base[i] == COMMENT_CHAR
			|| base[i] == DIRECT_CHAR || base[i] == SEPARATOR_CHAR
			|| base[i] == EOL || base[i] == MINUS || base[i] == STRING_CHAR)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/*
** @desc init function to assert
**       if the define set is correct
**       for processing;
** @params i iterators
** @return Bool[Success];
*/

t_bool			check_collisions(const char *base,
						const char *labels,
						const char *n_cmd,
						const char *c_cmd)
{
	if (!(labels_check(labels, 0))
		|| !(base_check(base, 0))
		|| ft_strlen(n_cmd) > PROG_NAME_LENGTH
		|| ft_strlen(c_cmd) > COMMENT_LENGTH)
		return (FALSE);
	return (TRUE);
}
