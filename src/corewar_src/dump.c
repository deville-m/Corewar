/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomonad <iomonad@riseup.net>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 21:18:42 by iomonad           #+#    #+#             */
/*   Updated: 2018/05/22 22:38:38 by iomonad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

/*
** @desc This is the visual meat.
**       dump to ncurse mem current
**       memory state
** @param mem memory ncurses scene
** @param arena game info structure
** @return nil
*/

static void	apply_memory(WINDOW *mem,
				t_arena *arena)
{
	return ;
}

/*
** @desc Apply infos to the state bar
** @param info side info/bordel scene
** @param arena game info structure
** @return nil
*/

static void apply_sidebar(WINDOW *status,
				t_arena *arena)
{
	int x;
	int y;

	getmaxyx(status, y, x);
	wattron(status, A_BOLD);
	mvwprintw(status, y/6 + 2, x/5, "Cycle: %d", arena->clock);
	mvwprintw(status, y/6 + 4, x/5, "Processes: %d", 1223);
	mvwprintw(status, y/6 + 6, x/5, "-------");
	mvwprintw(status, y/6 + 8, x/5, "CYCLE_TO_DIE: %d", CYCLE_TO_DIE);
	mvwprintw(status, y/6 + 10, x/5, "CYCLE_DELTA: %d", CYCLE_DELTA);
	mvwprintw(status, y/6 + 12, x/5, "NBR_LIVE: %d", NBR_LIVE);
	mvwprintw(status, y/6 + 14, x/5, "MAX_CHECKS: %d", MAX_CHECKS);
	wrefresh(status);
	wattroff(status, A_BOLD);
}

/*
** @desc dump current memory to the windows
**       then update the scene.
** @param mem memory ncurses scene
** @param info side info/bordel scene
** @param arena game info structure
** @return nil
*/

void		dump_cycle_memory(WINDOW *mem, WINDOW *info,
					t_arena *arena)
{
	apply_memory(mem, arena);
	apply_sidebar(info, arena);
}
