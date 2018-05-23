/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 16:05:06 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/23 16:16:01 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

void	add(t_arena *map, t_process *proc)
{
	unsigned int	a;
	unsigned int	b;

	a = proc->reg[proc->param[0].data.reg_nbr];
	b = proc->reg[proc->param[1].data.reg_nbr];
	swap_endian(&a, 4);
	swap_endian(&b, 4);
	a = a + b;
	swap_endian(&a, 4);
	proc->reg[proc->param[2].data.reg_nbr] = a;
	if (a == 0)
		proc->carry = 1;
	else
		proc->carry = 0;
}

void	sub(t_arena *map, t_process *proc)
{
	unsigned int	a;
	unsigned int	b;

	a = proc->reg[proc->param[0].data.reg_nbr];
	b = proc->reg[proc->param[1].data.reg_nbr];
	swap_endian(&a, 4);
	swap_endian(&b, 4);
	a = a - b;
	swap_endian(&a, 4);
	proc->reg[proc->param[2].data.reg_nbr] = a;
	if (a == 0)
		proc->carry = 1;
	else
		proc->carry = 0;
}
