/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 16:04:03 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/24 18:47:45 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

void	ld(t_arena *map, t_process *proc)
{
	unsigned char	buf[4];
	unsigned int	dir;
	short			ind;
	int				npc;

	if (proc->param[0].type == INDIRECT)
	{
		ind = proc->param[0].data.indirect;
		swap_endian(&ind, IND_SIZE);
		npc = proc->pc + ((int)ind % IDX_MOD);
		if (vm_read((void *)map->memory, npc, buf, 4) == 4)
		{
			trad_input(buf, &(proc->reg[proc->param[1].data.reg_nbr]), 4);
			swap_endian(&(proc->reg[proc->param[1].data.reg_nbr]), 4);
		}
	}
	else
	{
		dir = proc->param[0].data.direct;
		swap_endian(&dir, IND_SIZE);
		proc->reg[proc->param[1].data.reg_nbr] = dir;
	}
	if (proc->reg[proc->param[1].data.reg_nbr] == 0)
		proc->carry = 1;
	else
		proc->carry = 0;
}
