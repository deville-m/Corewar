/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 16:04:51 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/28 17:10:36 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

void	st(t_arena *map, t_process *proc)
{
	int				npc;
	short			ind;
	unsigned int	tmp;

	if (proc->param[1].type == REGISTER)
	{
		tmp = proc->reg[proc->param[0].data.reg_nbr];
		proc->reg[proc->param[1].data.reg_nbr] = tmp;
	}
	else
	{
		ind = proc->param[1].data.indirect;
		swap_endian(&ind, 2);
		npc = proc->pc + (ind % IDX_MOD);
		tmp = proc->reg[proc->param[0].data.reg_nbr];
		swap_endian(&tmp, 4);
		vm_write(map->memory, npc, (void *)&(tmp), 4);
	}
}
