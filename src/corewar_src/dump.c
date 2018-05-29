/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomonad <iomonad@riseup.net>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 21:18:42 by iomonad           #+#    #+#             */
/*   Updated: 2018/05/29 09:27:18 by ctrouill         ###   ########.fr       */
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

static void		apply_memory(WINDOW *mem,
				t_arena *arena, int x, int y)
{
	size_t		i;
	int			xx;
	int			yy;

	init_values(&i, &xx, &yy);
	getmaxyx(mem, y, x);
	while (i < MEM_SIZE)
	{
		if (arena->memory[i] == 0x00 &&
			player_ownership(arena->ownership[i], arena) == FALSE)
			wattron(mem, COLOR_PAIR(7));
		else if (arena->memory[i] == 0x00
			&& player_ownership(arena->ownership[i], arena) == TRUE)
			wattron(mem, A_BOLD);
		else
			wattron(mem, COLOR_PAIR(icolors(arena->ownership[i], arena)));
		if (apply_pc(arena, i) == TRUE)
		{
			wattron(mem, COLOR_PAIR(7));
			wattron(mem, A_STANDOUT);
		}
		mvwprintw(mem, yy, xx, "%.2x", arena->memory[i]);
		if ((xx + 7 > x))
		{
			xx = 1;
			yy += 1;
		}
		else
			xx += 3;
		wattroff(mem, A_STANDOUT);
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

void			dump_cycle_memory(t_scene *scene, t_arena *arena)
{
	apply_memory(scene->memory, arena, 0, 0);
	print_status(scene, (int)arena->clock,
		ft_dlstlen(arena->procs), arena);
}
