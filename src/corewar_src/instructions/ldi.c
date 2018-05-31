/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 12:27:10 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/31 13:53:03 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ldi(t_arena *map, t_process *proc)
{
	unsigned int	result;
	int				a;
	int				b;
	int				npc;

	if (proc->param[0].type == REGISTER)
		a = proc->reg[proc->param[0].data.reg_nbr];
	else
		a = (int)read_whatever_index(map, proc, 0);
	if (proc->param[1].type == REGISTER)
		b = proc->reg[proc->param[1].data.reg_nbr];
	else
		b = (int)read_whatever_index(map, proc, 1);
	a = a + b;
	npc = proc->pc + (a % IDX_MOD);
	result = go_read_label(map, npc);
	proc->reg[proc->param[2].data.reg_nbr] = result;
}
