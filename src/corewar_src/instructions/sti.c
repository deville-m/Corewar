/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 13:46:50 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/28 17:16:42 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	sti(t_arena *map, t_process *proc)
{
	unsigned int	result;
	short			a;
	short			b;
	int				npc;

	a = read_whatever_index(proc, 1);
	swap_endian(&a, 2);
	b = read_whatever_index(proc, 2);
	swap_endian(&b, 2);
	a = a + b;
	// le sujet d'Epitech indique le modulo, pas le 42. Je ne sais a quel saint
	// me vouer.
	npc = proc->pc + ((int)a % IDX_MOD);
	result = proc->reg[proc->param[0].data.reg_nbr];
	swap_endian(&result, 4);
	vm_write(map->memory, npc, (void *)&(result), 4);
}
