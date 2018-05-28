/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 12:21:09 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/28 18:32:23 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	lld(t_arena *map, t_process *proc)
{
	unsigned int	dir;
	short			ind;
	int				npc;

	if (proc->param[0].type == INDIRECT)
	{
		ind = proc->param[0].data.indirect;
		swap_endian(&ind, 2);
		npc = proc->pc + (int)ind;
		dir = go_read_label(map, npc);
	}
	else
		dir = proc->param[0].data.direct;
	swap_endian(&dir, 4);
	proc->reg[proc->param[1].data.reg_nbr] = dir;
	update_carry(proc, proc->reg[proc->param[1].data.reg_nbr]);
}
