/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:33:29 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/23 11:20:31 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static void			alloc_processus(t_arena *arena,
									uint16_t actor,
									size_t offset)
{
	t_process		process;

	process.pc = offset;
	process.carry = FALSE;
	process.alive = FALSE;
	process.wait = 0;
	process.reg[0] = arena->players[actor].id;
	process.instruction = NULL;
	ft_bzero(&process.op, sizeof(t_op));
	ft_bzero(process.param, sizeof(process.param));
	process.offset = 0;
	ft_dlstappend(&arena->procs,
		ft_dlstnew(&process, sizeof(t_process)));
}

static void 		init_memory(t_arena *arena,
							size_t k)
{
	unsigned short	actor;
	size_t			offset;

	offset = 0;
	actor = 0;
	ft_bzero(arena->memory, MEM_SIZE);
	ft_bzero(arena->ownership, MEM_SIZE);
	while (actor < arena->np)
	{
		ft_memcpy(arena->memory + offset, arena->players[actor].exec,
			arena->players[actor].header.prog_size);
		ft_memset(arena->ownership + offset, arena->players[actor].id,
			arena->players[actor].header.prog_size);
		alloc_processus(arena, actor, offset);
		offset += (MEM_SIZE / arena->np);
		actor++;
	}
}

/*
** Initialise the arena
** with default values
** and place users memory
*/

void	init_arena(t_arena *arena)
{
	/*
	** TODO:
	** - Dump a equidistance du exec des players
	**   + set ownership en fct des ID des joueurs
	** - Spawner 2 proc ou le pc pointe vers le dbt de chq joueurs
	**   + Initialiser le registre `R1` en fct des id des jrs
	**   + bzero sur tout les derniers
	*/
	arena->clock = 0;
	arena->procs = NULL;
	arena->cycle_to_die = CYCLE_TO_DIE;
	ft_memset(arena->memory, 0xff, MEM_SIZE);
	init_memory(arena, 0);
	dump_memory(arena->memory, arena->ownership, 0);
}
