/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 12:27:10 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/28 14:14:14 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ldi(t_arena *map, t_process *proc)
{
	unsigned int	result;
	short			a;
	short			b;
	int				npc;

	a = read_whatever_index(proc, 0);
	b = read_whatever_index(proc, 1);
	a = a + b;
	// le sujet d'Epitech indique le modulo, pas le 42. Je ne sais a quel saint
	// me vouer.
	npc = proc->pc + ((int)a % IDX_MOD);
	result = go_read_label(map, npc);
	swap_endian(&result, 4);
	proc->reg[proc->param[2].data.reg_nbr] = result;
	// Epitech precise le carry, pas 42...
	update_carry(proc, result);
}
