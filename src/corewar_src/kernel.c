/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 09:16:38 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/24 09:47:27 by ctrouill         ###   ########.fr       */
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
	if (options->trash == TRUE)
		dump_player_exec(arena);
	init_arena(arena, options);
	while (arena->procs && arena->clock < 20) /* TODO: modifier la condition */
	{
		exec_processes(arena);
		if (arena->clock && arena->clock % arena->cycle_to_die == 0)
			if (proc_filter(&arena->procs) > NBR_LIVE)
				arena->cycle_to_die -= CYCLE_DELTA;
		verbose(arena, 3);
		++arena->clock;
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
	t_scene	scene;

	if (options->trash == TRUE)
		dump_player_exec(arena);
	init_arena(arena, options);
	init_curses();
	alloc_window(&scene, arena);
	while (arena->procs) /* TODO: modifier la condition */
	{
		keybindinds_callback(wgetch(scene.memory));
		exec_processes(arena);
		if (arena->clock && arena->clock % arena->cycle_to_die == 0)
			if (proc_filter(&arena->procs) > NBR_LIVE)
				arena->cycle_to_die -= CYCLE_DELTA;
		dump_cycle_memory(&scene, arena);
		refresh();
		++arena->clock;
		usleep(10000);
	}
	free(scene.memory);
	free(scene.sidebar);
	return (TRUE);
}
