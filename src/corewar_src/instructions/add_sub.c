/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 16:05:06 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/28 16:10:22 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	add(t_arena *map, t_process *proc)
{
	unsigned int	a;
	unsigned int	b;

	(void)map->cycle_to_die;
	a = proc->reg[proc->param[0].data.reg_nbr];
	b = proc->reg[proc->param[1].data.reg_nbr];
	swap_endian(&a, 4);
	swap_endian(&b, 4);
	a = a + b;
	swap_endian(&a, 4);
	proc->reg[proc->param[2].data.reg_nbr] = a;
	update_carry(proc, a);
}

void	sub(t_arena *map, t_process *proc)
{
	unsigned int	a;
	unsigned int	b;
	unsigned char	c;
	unsigned char	d;

	(void)map->cycle_to_die;
	c = proc->param[0].data.reg_nbr;
	d = proc->param[1].data.reg_nbr;
	a = proc->reg[c];
	b = proc->reg[d];
	swap_endian(&a, 4);
	swap_endian(&b, 4);
	a = a - b;
	swap_endian(&a, 4);
	proc->reg[proc->param[2].data.reg_nbr] = a;
	update_carry(proc, a);
}
