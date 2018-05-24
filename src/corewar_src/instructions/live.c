/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 14:32:19 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/24 14:51:59 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

void	live(t_arena *map, t_process *proc)
{
	int				i;
	unsigned int	value;

	proc->alive += 1;
	i = 0;
	value = proc->param[0].data.direct;
	swap_endian(&value, DIR_SIZE);
	while (i < map->np)
	{
		if (value == map->players[i].id)
			map->players[i].last_live = map->clock;
		i += 1;
	}
}