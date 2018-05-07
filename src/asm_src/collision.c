/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 17:14:33 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/07 17:45:29 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

/*
** @desc init function to assert
**       if the define set is correct
**       for processing;
** @params i iterators
** @return Bool[Success];
*/

t_bool			check_collisions(uint_fast32_t i)
{
	const char	*base;
	const char	*labels;

	base = (const char*)BASE;
	labels = (const char*)LABEL_CHARS;
	while (labels[i] != '\0')
	{
		/* TODO: Classify types */
		if (labels[i] == LABEL_CHAR
			|| labels[i] == COMMENT_CHAR
			|| labels[i] == DIRECT_CHAR
			|| labels[i] == SEPARATOR_CHAR)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
