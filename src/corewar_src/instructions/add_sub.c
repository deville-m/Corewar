/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 16:05:06 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/28 19:00:43 by rbaraud          ###   ########.fr       */
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
	a = a + b;
	proc->reg[proc->param[2].data.reg_nbr] = a;
	update_carry(proc, a);
}

void	sub(t_arena *map, t_process *proc)
{
	unsigned int	a;
	unsigned int	b;

	(void)map->cycle_to_die;
	a = proc->param[0].data.reg_nbr;
	b = proc->param[1].data.reg_nbr;
	a = a - b;
	proc->reg[proc->param[2].data.reg_nbr] = a;
	update_carry(proc, a);
}
