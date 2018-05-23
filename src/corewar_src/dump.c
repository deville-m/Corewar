/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomonad <iomonad@riseup.net>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 21:18:42 by iomonad           #+#    #+#             */
/*   Updated: 2018/05/23 17:07:31 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static t_bool		player_ownership(unsigned int player)
{
	if (player == 0xFF
		|| player == 0xFE
		|| player == 0xFD
		|| player == 0xFC)
		return (TRUE);
	return (FALSE);
}

static t_bool		apply_pc(t_arena *arena,
							 int i)
{
	t_dlist			*walk;
	t_process		*cur;

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
		if (arena->memory[i] == 0xff && !player_ownership(arena->ownership[i]))
			wattron(mem, COLOR_PAIR(6));
		else if (arena->memory[i] == 0x00)
			wattron(mem, A_BOLD);
		else
			wattron(mem, COLOR_PAIR(icolors(arena->ownership[i])));
		if (apply_pc(arena, i) == TRUE)
			wattron(mem, A_STANDOUT);
		mvwprintw(mem, yy, xx, "%.2x", arena->memory[i]);
		if ((xx % (x - 2) == 0))
		{
			xx = 1;
			yy += 1;
		}
		else
			xx += 3;
		wattroff(mem, A_STANDOUT );
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
