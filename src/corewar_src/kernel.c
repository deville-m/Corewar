/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 09:16:38 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/11 14:24:56 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

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

	init_curses();
	/* init_arena(arena)*/
	while (arena->processes != NULL)
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
