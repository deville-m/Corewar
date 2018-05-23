/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomonad <iomonad@riseup.net>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 21:18:42 by iomonad           #+#    #+#             */
/*   Updated: 2018/05/23 15:03:26 by mdeville         ###   ########.fr       */
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
		t_arena *arena, int x, int y)
{
	size_t i = 0;
	int xx = 1, yy = 1;

	getmaxyx(mem, y, x);
	while (i < MEM_SIZE) {
		if (arena->memory[i] == 0xff)
			attron(COLOR_PAIR(icolors(arena->ownership[i])));
		else if (arena->memory[i] == 0x00)
			attron(COLOR_PAIR(icolors(arena->ownership[i])));
		else
			attroff(COLOR_PAIR(6));
		mvwprintw(mem, yy, xx, "%.2x", arena->memory[i]);
		if ((xx % (x - 2) == 0))
		{
			xx = 1;
			yy += 1;
		}
		else
			xx += 3;
		i++;
	}
	wrefresh(mem);
	return ;
}

/*
** @desc dump current memory to the windows
**       then update the scene.
** @param mem memory ncurses scene
** @param info side info/bordel scene
** @param arena game info structure
** @return nil
*/

void		dump_cycle_memory(t_scene *scene, t_arena *arena)
{
	apply_memory(scene->memory, arena, 0, 0);
	print_status(scene, (int)arena->clock,
		ft_dlstlen(arena->procs));
}
