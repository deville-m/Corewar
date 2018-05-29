/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 14:13:45 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/29 17:50:56 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	lldi(t_arena *map, t_process *proc)
{
	unsigned int	result;
	short			a;
	short			b;
	int				npc;

	a = read_whatever_index(map, proc, 0);
	b = read_whatever_index(map, proc, 1);
	a = a + b;
	npc = proc->pc + (int)a;
	result = go_read_label(map, npc);
	proc->reg[proc->param[2].data.reg_nbr] = result;
	update_carry(proc, result);
}
