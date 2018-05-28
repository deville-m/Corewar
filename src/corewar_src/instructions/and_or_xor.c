/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_xor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 11:29:03 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/28 12:16:44 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static unsigned int	find_bitwise_params(t_arena *map, t_process *proc, int nbr)
{
	unsigned int	result;

	if (proc->param[nbr].type == INDIRECT)
		result = go_read_label(map, (int)proc->param[nbr].data.indirect);
	else if (proc->param[nbr].type == DIRECT)
	{
		result = proc->param[nbr].data.direct;
		swap_endian(&result, 4);
	}
	else
		result = proc->reg[proc->param[nbr].data.reg_nbr];
	return (result);
}

void				and(t_arena *map, t_process *proc)
{
	unsigned int	a;

	a = find_bitwise_params(map, proc, 0) & find_bitwise_params(map, proc, 1);
	if (proc->param[2].type == REGISTER)
	{
		update_carry(proc, a);
		proc->reg[proc->param[2].data.reg_nbr] = a;
	}
}

void				or(t_arena *map, t_process *proc)
{
	unsigned int	a;

	a = find_bitwise_params(map, proc, 0) | find_bitwise_params(map, proc, 1);
	if (proc->param[2].type == REGISTER)
	{
		update_carry(proc, a);
		proc->reg[proc->param[2].data.reg_nbr] = a;
	}
}

void				xor(t_arena *map, t_process *proc)
{
	unsigned int	a;

	a = find_bitwise_params(map, proc, 0) ^ find_bitwise_params(map, proc, 1);
	if (proc->param[2].type == REGISTER)
	{
		update_carry(proc, a);
		proc->reg[proc->param[2].data.reg_nbr] = a;
	}
}
