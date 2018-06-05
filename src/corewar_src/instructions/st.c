/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 16:04:51 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/31 13:50:17 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

void	st(t_arena *map, t_process *proc)
{
	int				npc;
	short			ind;
	unsigned int	tmp;

	tmp = proc->reg[proc->param[0].data.reg_nbr];
	if (proc->param[1].type == REGISTER)
		proc->reg[proc->param[1].data.reg_nbr] = tmp;
	else
	{
		ind = proc->param[1].data.indirect;
		swap_endian(&ind, 2);
		npc = proc->pc + ((int)ind % IDX_MOD);
		swap_endian(&tmp, 4);
		own_write(map->ownership, npc, map->ownership[proc->pc], 4);
		vm_write(map->memory, npc, (void *)&(tmp), 4);
	}
}
