/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_bit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 13:18:01 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/22 13:18:20 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

void	and(t_arena *map, t_process *proc)
{
	unsigned int	a;
	unsigned int	b;
	unsigned char	buf[4];
	short			ind;

	proc->carry = 1;
	if (proc->param[0].type == INDIRECT)
	{
		ind = proc->param[0].data.indirect;
		if (vm_read((void *)map->memory, proc->pc + (int)ind, buf, 4) != 4)
		{
			proc->carry = 0;
			return ;
		}
		trad_input(&buf[0], &a, 4);
	}
	else
	{
		a = proc->reg[proc->param[0].data.reg_nbr];
		if (proc->param[0].type == REGISTER)	
			swap_endian(&a, 4);
	}
	if (proc->param[1].type == INDIRECT)
	{
		ind = proc->param[1].data.indirect;
		if (vm_read((void *)map->memory, proc->pc + (int)ind, buf, 4) != 4)
		{
			proc->carry = 0;
			return ;
		}
		trad_input(&buf[0], &b, 4);
	}
	else
	{
		b = proc->reg[proc->param[1].data.reg_nbr];
		if (proc->param[1].type == REGISTER)	
			swap_endian(&b, 4);
	}
	a = a & b;
	swap_endian(&a, 4);
	proc->reg[proc->param[2].data.reg_nbr] = a;
}

void	or(t_arena *map, t_process *proc)
{
	unsigned int	a;
	unsigned int	b;
	unsigned char	buf[4];
	short			ind;

	proc->carry = 1;
	if (proc->param[0].type == INDIRECT)
	{
		ind = proc->param[0].data.indirect;
		if (vm_read((void *)map->memory, proc->pc + (int)ind, buf, 4) != 4)
		{
			proc->carry = 0;
			return ;
		}
		trad_input(&buf[0], &a, 4);
	}
	else
	{
		a = proc->reg[proc->param[0].data.reg_nbr];
		if (proc->param[0].type == REGISTER)	
			swap_endian(&a, 4);
	}
	if (proc->param[1].type == INDIRECT)
	{
		ind = proc->param[1].data.indirect;
		if (vm_read((void *)map->memory, proc->pc + (int)ind, buf, 4) != 4)
		{
			proc->carry = 0;
			return ;
		}
		trad_input(&buf[0], &b, 4);
	}
	else
	{
		b = proc->reg[proc->param[1].data.reg_nbr];
		if (proc->param[1].type == REGISTER)	
			swap_endian(&b, 4);
	}
	a = a | b;
	swap_endian(&a, 4);
	proc->reg[proc->param[2].data.reg_nbr] = a;
}

void	xor(t_arena *map, t_process *proc)
{
	unsigned int	a;
	unsigned int	b;
	unsigned char	buf[4];
	short			ind;

	proc->carry = 1;
	if (proc->param[0].type == INDIRECT)
	{
		ind = proc->param[0].data.indirect;
		if (vm_read((void *)map->memory, proc->pc + (int)ind, buf, 4) != 4)
		{
			proc->carry = 0;
			return ;
		}
		trad_input(&buf[0], &a, 4);
	}
	else
	{
		a = proc->reg[proc->param[0].data.reg_nbr];
		if (proc->param[0].type == REGISTER)	
			swap_endian(&a, 4);
	}
	if (proc->param[1].type == INDIRECT)
	{
		ind = proc->param[1].data.indirect;
		if (vm_read((void *)map->memory, proc->pc + (int)ind, buf, 4) != 4)
		{
			proc->carry = 0;
			return ;
		}
		trad_input(&buf[0], &b, 4);
	}
	else
	{
		b = proc->reg[proc->param[1].data.reg_nbr];
		if (proc->param[1].type == REGISTER)	
			swap_endian(&b, 4);
	}
	a = a ^ b;
	swap_endian(&a, 4);
	proc->reg[proc->param[2].data.reg_nbr] = a;
}
