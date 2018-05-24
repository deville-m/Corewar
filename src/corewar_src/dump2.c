/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <iomonad@riseup.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 10:28:34 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/24 10:42:35 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

/*
** @desc Determine \x00 ownership
** @param player player id
** @return bool
*/

t_bool		player_ownership(unsigned int player)
{
	if (player == 0xFF
		|| player == 0xFE
		|| player == 0xFD
		|| player == 0xFC)
		return (TRUE);
	return (FALSE);
}

/*
** @desc norm helper
** @return nil
*/

void		init_values(size_t *i, int *xx,
					int *yy)
{
	*i = 0;
	*xx = 0;
	*yy = 0;
}

/*
** @desc Predicate to determine
**       if PC must be set on the
**       current cursor.
** @param arena game info structure
** @param i current memory cursor
** @return boolean
*/

t_bool		apply_pc(t_arena *arena,
				int i)
{
	t_dlist		*walk;
	t_process	*cur;

	walk = arena->procs;
	while (walk != NULL)
	{
		cur = (t_process*)walk->content;
		if (cur->pc == i)
			return (TRUE);
		walk = walk->next;
	}
	return (FALSE);
}

uint8_t		icolors(unsigned char owner)
{
	if (owner == 0xFF)
		return (1);
	else if (owner == 0xFE)
		return (2);
	else if (owner == 0xFD)
		return (3);
	else if (owner == 0xFC)
		return (4);
	return (5);
}
