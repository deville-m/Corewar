/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 17:54:39 by mdeville          #+#    #+#             */
/*   Updated: 2018/05/17 18:23:46 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

static t_bool	set_op(unsigned char op_code, t_op *op)
{
	size_t i;

	i = 0;
	while (i < INSTRUCTION_NBR)
	{
		if (g_op_tab[i].op_code == op_code)
		{
			*op = g_op_tab[i];
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

static t_bool	parse_direct(
							t_arena *arena,
							t_process *proc,
							size_t i)
{
	t_bool success;
	t_bool index;

	success = TRUE;
	index = (proc->op.index) ? TRUE : FALSE;
	if (!(proc->op.arg_type[i] & T_DIR))
		success = FALSE;
	vm_read(arena->memory, proc->pc + proc->offset,
			&proc->params[i].data.direct, index ? IND_SIZE : DIR_SIZE);
	proc->offset += (index) ? IND_SIZE : DIR_SIZE;
	return (success);
}

static t_bool	parse_param(
							t_arena *arena,
							t_process *proc,
							unsigned char type,
							size_t index)
{
	t_bool success;

	success = TRUE;
	if (type == T_REG)
	{
		if (!(proc->op.arg_type[index] & T_REG))
			success = FALSE;
		proc->params[index].type = REGISTER;
		vm_read(arena->memory, proc->pc + proc->offset,
				&proc->params[index].data.reg_nbr, 1);
		++proc->offset;
	}
	else if (type == T_DIR)
		success = parse_direct(arena, proc, index);
	else if (type == T_IND)
	{
		if (!(proc->op.arg_type[index] & T_IND))
			success = FALSE;
		vm_read(arena->memory, proc->pc + proc->offset,
				&proc->params[index].data.indirect, IND_SIZE);
		proc->offset += IND_SIZE;
	}
	return (success);
}

static t_bool	set_params(t_arena *arena, t_process *proc)
{
	size_t			i;
	unsigned char	encoding_byte;
	t_bool			success;

	proc->offset = 1;
	if (!proc->op.coding_byte)
		encoding_byte = proc->op.arg_type[0];
	else
	{
		encoding_byte = arena->memory[(proc->pc + 1) % MEM_SIZE];
		++proc->offset;
	}
	success = TRUE;
	i = 0;
	while (encoding_byte)
	{
		if (!parse_param(arena, proc, encoding_byte & 0XC0, i))
			success = FALSE;
		++i;
		encoding_byte <<= 2;
	}
	return (success);
}

void			check_process(t_arena *arena, t_dlist *elem)
{
	t_process *proc;

	proc = (t_process *)elem;
	if (arena->clock != proc->wait)
		return ;
	proc->wait = 0;
	if (proc->instruction)
		proc->instruction(arena, proc);
	proc->pc = (proc->pc + proc->offset) % MEM_SIZE;
	if (proc->pc < 0)
		proc->pc = MEM_SIZE + proc->pc;
	else
		proc->pc = MEM_SIZE - (proc->offset - proc->pc);
	if (!set_op(arena->memory[proc->pc], &proc->op))
	{
		proc->instruction = NULL;
		proc->offset = 1;
		return ;
	}
	proc->wait = proc->op.cycle_cost + arena->clock;
	if (set_params(arena, proc) == FALSE)
		proc->instruction = NULL;
	else
		set_instruction(proc, proc->op.op_code);
}
