/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 17:54:39 by mdeville          #+#    #+#             */
/*   Updated: 2018/06/05 11:43:26 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

static int			parse_reg(
							t_arena *arena,
							t_process *proc,
							size_t i)
{
	int				success;

	success = 1;
	if (!(proc->op.arg_type[i] & T_REG))
		success = 0;
	proc->param[i].type = REGISTER;
	vm_read(arena->memory, proc->pc + proc->offset,
			&proc->param[i].data.reg_nbr, 1);
	if (proc->param[i].data.reg_nbr <= 0
		|| proc->param[i].data.reg_nbr > REG_NUMBER)
		success = 0;
	++proc->offset;
	return (success);
}

static int			parse_direct(
							t_arena *arena,
							t_process *proc,
							size_t i)
{
	int				success;
	int				index;

	success = 1;
	index = (proc->op.index) ? 1 : 0;
	if (!(proc->op.arg_type[i] & T_DIR))
		success = 0;
	proc->param[i].type = DIRECT;
	vm_read(arena->memory, proc->pc + proc->offset,
			&proc->param[i].data, index ? IND_SIZE : DIR_SIZE);
	proc->offset += (index) ? IND_SIZE : DIR_SIZE;
	return (success);
}

static int			parse_param(
							t_arena *arena,
							t_process *proc,
							unsigned char type,
							size_t index)
{
	int				success;

	success = 1;
	if (type == (REG_CODE << 6))
		success = parse_reg(arena, proc, index);
	else if (type == (DIR_CODE << 6))
		success = parse_direct(arena, proc, index);
	else if (type == (IND_CODE << 6))
	{
		if (!(proc->op.arg_type[index] & T_IND) || !vm_read(arena->memory,
		proc->pc + proc->offset, &proc->param[index].data.indirect, IND_SIZE))
			success = 0;
		proc->param[index].type = INDIRECT;
		proc->offset += IND_SIZE;
	}
	else
		success = 0;
	return (success);
}

static int			set_params(t_arena *arena, t_process *proc)
{
	int				i;
	unsigned char	encoding_byte;
	int				success;

	proc->offset = 1;
	if (!proc->op.coding_byte)
		encoding_byte = proc->op.arg_type[0] << 6;
	else
	{
		encoding_byte = arena->memory[(proc->pc + 1) % MEM_SIZE];
		++proc->offset;
	}
	success = 1;
	i = 0;
	while (i < proc->op.nb_param)
	{
		if (!parse_param(arena, proc, encoding_byte & 0XC0, i))
			success = 0;
		++i;
		encoding_byte <<= 2;
	}
	if (success && arena->opts->verbose & V_OP)
		print_exec(arena, proc);
	return (success);
}

void				check_process(t_arena *arena, t_dlist *elem)
{
	t_process		*proc;

	proc = (t_process *)elem->content;
	if (arena->clock != proc->wait)
		return ;
	if (proc->instruction)
	{
		if (set_params(arena, proc))
			proc->instruction(arena, proc);
		proc->wait = arena->clock + 1;
		proc->instruction = NULL;
		return ;
	}
	if ((proc->pc = (proc->pc + proc->offset) % MEM_SIZE) < 0)
		proc->pc = MEM_SIZE + proc->pc;
	if (!set_op(arena->memory[proc->pc], &proc->op))
	{
		proc->offset = 1;
		proc->wait = arena->clock + 1;
		return ;
	}
	proc->wait = proc->op.cycle_cost + arena->clock - 1;
	set_instruction(proc, proc->op.op_code);
	if (arena->opts->verbose & V_OP)
		ft_printf("%s at %d, wait = %u\n", proc->op.name, proc->pc, proc->wait);
}
