/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:33:29 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/14 19:41:27 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

#define CUR_PLAYER 2

static void init_memory(char *memory,
						char *ownership,
						t_player *players,
						size_t k)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (i < CUR_PLAYER)
	{
		while (players[i].exec[j] != '\0')
		{
			memory[k] = players[i].exec[j];
			j++;
		}
		i++;
	}
}

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
	init_memory(arena->memory, arena->ownership, arena->players, 0);
	return ;
}
