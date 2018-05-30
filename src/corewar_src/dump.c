/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomonad <iomonad@riseup.net>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 21:18:42 by iomonad           #+#    #+#             */
/*   Updated: 2018/05/30 14:40:35 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static void		apply_memory_bis(int *xx, int *yy,
						int *x, size_t *i)
{
	if ((*xx + 7 > *x))
	{
		*xx = 1;
		*yy += 1;
	}
	else
		*xx += 3;
	*i += 1;
}

/*
** @desc This is the visual meat.
**       dump to ncurse mem current
**       memory state
** @param mem memory ncurses scene
** @param arena game info structure
** @return nil
*/

static void		apply_memory(WINDOW *mem,
				t_arena *a, int x, int y)
{
	size_t		i;
	int			xx;
	int			yy;

	init_values(&i, &xx, &yy);
	getmaxyx(mem, y, x);
	while (i < MEM_SIZE)
	{
		if (player_ownership(a->ownership[i], a))
			wattron(mem, COLOR_PAIR(icolors(a->ownership[i], a)));
		else
		{
			wattron(mem, COLOR_PAIR(7));
			wattron(mem, A_BOLD);
		}
		if (apply_pc(a, i) == TRUE)
		{
			wattron(mem, A_STANDOUT);
			wattron(mem, COLOR_PAIR(0));
		}
		mvwprintw(mem, yy, xx, "%.2x", a->memory[i]);
		apply_memory_bis(&xx, &yy, &x, &i);
		wattroff(mem, A_STANDOUT);
	}
	wrefresh(mem);
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
