/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 13:46:50 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/31 13:54:19 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	sti(t_arena *map, t_process *proc)
{
	unsigned int	result;
	int				a;
	int				b;
	int				npc;

	if (proc->param[1].type == REGISTER)
		a = proc->reg[proc->param[1].data.reg_nbr];
	else
		a = (int)read_whatever_index(map, proc, 1);
	if (proc->param[2].type == REGISTER)
		b = proc->reg[proc->param[2].data.reg_nbr];
	else
		b = (int)read_whatever_index(map, proc, 2);
	a = a + b;
	npc = proc->pc + (a % IDX_MOD);
	result = proc->reg[proc->param[0].data.reg_nbr];
	swap_endian(&result, 4);
	own_write(map->ownership, npc, map->ownership[proc->pc], 4);
	vm_write(map->memory, npc, (void *)&(result), 4);
}
