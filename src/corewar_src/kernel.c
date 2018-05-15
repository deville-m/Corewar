/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 09:16:38 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/15 09:52:51 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <commons.h>

/*
** @desc monothilic part of the arena
**       arena.players should be init
**       before fun call.
** @param options retrieved
** @return nil
*/

t_bool		kernel(struct s_option *options, t_arena *arena)
{
	WINDOW 	*warena = NULL;
	WINDOW	*status = NULL;

	for (size_t p = 0; p < arena->np; p++) {
		printf("\n\nPlayer[%zu]: ", p);
		swap_endian(&arena->players[p].header.prog_size, sizeof(arena->players[p].header.prog_size));
		for (size_t i = 0; i < arena->players[p].header.prog_size; i++) {
			printf("\\x%x", arena->players[p].exec[i]);
		}
		printf("\n");
	}
	init_arena(arena);
	init_curses();
	while (arena->clock > 0) /* TODO: modifier la condition */
	{
		/*
		 * Graphics sections - plz ignore
		 */
		apply_windows(warena, status);
		wrefresh(warena);
		wrefresh(status);
		keybindinds_callback(getch());
	}
	free(warena);
	free(status);
	return (TRUE);
}
