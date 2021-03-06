/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 09:16:38 by ctrouill          #+#    #+#             */
/*   Updated: 2018/06/07 00:37:51 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <commons.h>

static void		exec_processes(t_arena *arena)
{
	t_dlist		*walk;

	walk = arena->procs;
	while (walk)
	{
		check_process(arena, walk);
		walk = walk->next;
	}
}

static void		verif(t_arena *arena, int verbose)
{
	static int	nb_check = 1;
	static int	count = 1;

	if (count >= arena->cycle_to_die)
	{
		count = 0;
		nb_check += 1;
		if (proc_filter(arena) > NBR_LIVE || nb_check == MAX_CHECKS)
		{
			nb_check = 0;
			arena->cycle_to_die -= CYCLE_DELTA;
			if (verbose & V_CLOCK)
				ft_printf("Cycle to die is now %d\n",
						arena->cycle_to_die);
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

int				kernel(struct s_option *options, t_arena *arena)
{
	print_player_headers(arena, 0);
	init_arena(arena, options);
	while (arena->procs)
	{
		++arena->clock;
		verbose(arena, arena->opts->verbose);
		verif(arena, arena->opts->verbose);
		exec_processes(arena);
		if (arena->clock >= arena->opts->dump)
			shut_up_and_take_my_memory(arena);
	}
	print_winner(arena, 0);
	return (1);
}

/*
** @desc monothilic part of the graphical arena
**       arena.players should be init
**       before fun call.
** @param options retrieved
** @return nil
*/

int				kernel_gfx(struct s_option *options, t_arena *arena)
{
	t_scene		scene;

	init_arena(arena, options);
	init_curses();
	alloc_window(&scene, arena);
	arena->opts->verbose = 0;
	while (arena->procs)
	{
		++arena->clock;
		dump_cycle_memory(&scene, arena);
		keybindinds_callback(getch(), &scene);
		verif(arena, arena->opts->verbose);
		exec_processes(arena);
		refresh();
		usleep(scene.speed);
	}
	print_winner_gfx(arena, 0, &scene, 0);
	delwin(scene.memory);
	delwin(scene.sidebar);
	return (1);
}
