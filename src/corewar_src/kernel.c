/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 09:16:38 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/30 17:40:14 by mdeville         ###   ########.fr       */
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

static void verif(t_arena *arena)
{
	static int nb_check = 0;
	static int count = 0;

	if (count >= arena->cycle_to_die)
	{
		count = 0;
		nb_check += 1;
		if (proc_filter(arena) > NBR_LIVE || nb_check == MAX_CHECKS)
		{
			nb_check = 0;
			arena->cycle_to_die -= CYCLE_DELTA;
		}
	}
	count += 1;
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
	init_arena(arena, options);
	while (arena->procs)
	{
		verif(arena);
		exec_processes(arena);
		verbose(arena, 3);
		if (arena->clock == arena->opts->dump)
			shut_up_and_take_my_memory(arena);
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

	init_arena(arena, options);
	init_curses();
	alloc_window(&scene, arena);
	while (arena->procs)
	{
		dump_cycle_memory(&scene, arena);
		keybindinds_callback(getch(), &scene);
		verif(arena);
		exec_processes(arena);
		refresh();
		++arena->clock;
		usleep(scene.speed);
	}
	free(scene.memory);
	free(scene.sidebar);
	endwin();
	print_winner(arena, 0);
	return (TRUE);
}
