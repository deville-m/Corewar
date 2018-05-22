/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 09:16:38 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/22 14:08:07 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <commons.h>

static void	exec_processes(t_arena *arena)
{
	t_dlist *walk;

	walk = arena->procs;
	while (walk)
	{
		check_process(arena, walk);
		walk = walk->next;
	}
}

/*
** @desc monothilic part of the arena
**       arena.players should be init
**       before fun call.
** @param options retrieved
** @return nil
*/

t_bool		kernel(struct s_option *options, t_arena *arena)
{
	dump_player_exec(arena);
	init_arena(arena);
	while (arena->procs) /* TODO: modifier la condition */
	{
		exec_processes(arena);
		if (arena->clock && arena->clock % arena->cycle_to_die == 0)
			if (proc_filter(&arena->procs) > NBR_LIVE)
				arena->cycle_to_die -= CYCLE_DELTA;
		++arena->clock;
	}
	return (TRUE);
}

/*
** @desc monothilic part of the graphical arena
**       arena.players should be init
**       before fun call.
** @param options retrieved
** @return nil
*/

t_bool		kernel_gfx(struct s_option *options, t_arena *arena)
{
	WINDOW 	*warena = NULL;
	WINDOW	*status = NULL;

	dump_player_exec(arena);
	init_arena(arena);
	init_curses();
	while (arena->procs) /* TODO: modifier la condition */
	{
		/* exec_processes(arena); */
		/* if (arena->clock && (arena->clock % arena->cycle_to_die) == 0) */
		/* 	if (proc_filter(&arena->procs) > NBR_LIVE) */
		/* 		arena->cycle_to_die -= CYCLE_DELTA; */
		++arena->clock;
		apply_windows(warena, status);
		wrefresh(warena);
		wrefresh(status);
		keybindinds_callback(getch());
	}
	free(warena);
	free(status);
	return (TRUE);
}
