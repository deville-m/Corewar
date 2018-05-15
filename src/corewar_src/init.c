/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:33:29 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/15 10:50:55 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static void 		init_memory(t_arena *arena,
							size_t k)
{
	size_t			cursor;
	unsigned short	actor;

	actor = 0;
	printf("Taille memoire: %d\n", MEM_SIZE);
	while (actor <= arena->np)
	{
		if (actor == 0)
		{
			cursor = 0;
			while (cursor < arena->players[0].header.prog_size)
			{
				arena->memory[cursor] = arena->players[0].exec[cursor];
				cursor++;
			}
		}
		if (actor == 1)
		{
			cursor = MEM_SIZE / 2;
			while (cursor < arena->players[1].header.prog_size)
			{
				arena->memory[cursor] = arena->players[1].exec[cursor];
				cursor++;
			}
		}
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
	 * TODO:
	 * - Dump a equidistance du exec des players
	 *   + set ownership en fct des ID des joueurs
	 * - Spawner 2 proc ou le pc pointe vers le dbt de chq joueurs
	 *   + Initialiser le registre `R1` en fct des id des jrs
	 *   + bzero sur tout les derniers
	 */
	arena->clock = 0;
	arena->cycle_to_die = CYCLE_TO_DIE;
	ft_memset(arena->memory, 0xff, MEM_SIZE);
	init_memory(arena, 0);
	dump_memory(arena->memory, 0);
}
