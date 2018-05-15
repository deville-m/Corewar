/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:33:29 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/15 14:08:16 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static void 		init_memory(t_arena *arena,
							size_t k)
{
	size_t			cursor;
	unsigned short	actor;
	size_t			i;
	size_t			offset;

	offset = 0;
	actor = 0;
	i = 0;
	cursor = 0;
	printf("Taille memoire: %d | nombres de joueurs: %d\n",
		   MEM_SIZE, arena->np);
	while (actor < arena->np) {
		ft_memcpy(arena->memory + offset, arena->players[actor].exec,
			arena->players[actor].header.prog_size);
		ft_memset(arena->ownership + offset, arena->players[actor].id,
			arena->players[actor].header.prog_size);
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
	arena->cycle_to_die = CYCLE_TO_DIE;
	ft_memset(arena->memory, 0xff, MEM_SIZE);
	init_memory(arena, 0);
	dump_memory(arena->memory, 0);
}
