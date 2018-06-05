/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <iomonad@riseup.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 10:28:34 by ctrouill          #+#    #+#             */
/*   Updated: 2018/06/05 11:36:30 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

/*
** @desc Determine \x00 ownership
** @param player player id
** @return bool
*/

int				player_ownership(unsigned int player,
					t_arena *arena)
{
	size_t		i;

	i = 0;
	while (i < arena->np)
	{
		if ((unsigned char)arena->players[i].id == player)
			return (1);
		i++;
	}
	return (0);
}

/*
** @desc norm helper
** @return nil
*/

void			init_values(size_t *i, int *xx,
					int *yy)
{
	*i = 0;
	*xx = 1;
	*yy = 1;
}

/*
** @desc Predicate to determine
**       if PC must be set on the
**       current cursor.
** @param arena game info structure
** @param i current memory cursor
** @return boolean
*/

int				apply_pc(t_arena *arena,
				int i)
{
	t_dlist		*walk;
	t_process	*cur;

	walk = arena->procs;
	while (walk != NULL)
	{
		cur = (t_process*)walk->content;
		if (cur->pc == i)
			return (1);
		walk = walk->next;
	}
	return (0);
}

uint8_t			icolors(unsigned char owner, t_arena *arena)
{
	size_t		i;

	i = 0;
	while (i < arena->np)
	{
		if ((unsigned char)arena->players[i].id == owner)
			return (i + 1);
		i++;
	}
	return (5);
}

void			shut_up_and_take_my_memory(t_arena *arena)
{
	dump_memory(arena->memory, arena->ownership, 0);
	exit(EXIT_SUCCESS);
}
