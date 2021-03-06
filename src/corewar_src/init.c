/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:33:29 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/31 10:21:47 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static void			alloc_processus(t_arena *arena,
									uint16_t actor,
									size_t offset)
{
	t_process		process;

	ft_bzero(&process.reg, sizeof(process.reg));
	process.pc = offset;
	process.carry = 0;
	process.alive = 0;
	process.wait = 1;
	process.reg[1] = arena->players[actor].id;
	process.instruction = NULL;
	ft_bzero(&process.op, sizeof(process.op));
	ft_bzero(&process.param, sizeof(process.param));
	process.offset = 0;
	ft_dlstprepend(&arena->procs,
		ft_dlstnew(&process, sizeof(t_process)));
}

static void			init_memory(t_arena *arena)
{
	unsigned short	actor;
	size_t			offset;

	offset = 0;
	actor = 0;
	ft_memset(arena->memory, 0x00, MEM_SIZE);
	ft_memset(arena->ownership, 0x00, MEM_SIZE);
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

void				init_arena(t_arena *arena, struct s_option *opts)
{
	(void)opts;
	arena->clock = 0;
	arena->procs = NULL;
	arena->cycle_to_die = CYCLE_TO_DIE;
	init_memory(arena);
}
