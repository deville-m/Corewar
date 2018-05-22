/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 09:16:38 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/22 22:38:00 by iomonad          ###   ########.fr       */
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
	print_player_headers(arena, 0);
	/* dump_player_exec(arena); */
	init_arena(arena);
	while (arena->procs && arena->clock < 100) /* TODO: modifier la condition */
	{
		exec_processes(arena);
		if (arena->clock && arena->clock % arena->cycle_to_die == 0)
			if (proc_filter(&arena->procs) > NBR_LIVE)
				arena->cycle_to_die -= CYCLE_DELTA;
		++arena->clock;
		verbose(arena, 3);
	}
	print_winner(arena, 0);
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

		/* ch = getch(); */
		/* keybindinds_callback(ch); */
		++arena->clock;
		apply_windows(warena, status);
		dump_cycle_memory(warena, status, arena);
		wrefresh(warena);
		wrefresh(status);
		refresh();
		fflush(stdout);
		usleep(10000);
	}
	free(warena);
	free(status);
	return (TRUE);
}
