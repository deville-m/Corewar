/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 17:54:39 by mdeville          #+#    #+#             */
/*   Updated: 2018/05/16 19:57:21 by mdeville         ###   ########.fr       */
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

static int		set_params(t_arena *arena, t_process *process)
{
	return (1);
}

static int		calc_offset(t_op op, unsigned char encoding_byte)
{
	int				offset;
	unsigned int	tmp;

	if (!op.coding_byte)
		encoding_byte = op.arg_type[0];
	offset = 0;
	while (encoding_byte)
	{
		tmp = encoding_byte & 0X03;
		if (tmp == T_REG)
			++offset;
		else if (tmp == T_DIR)
			offset += op.index ? IND_SIZE : DIR_SIZE;
		else if (tmp == T_IND)
			offset += IND_SIZE;
		encoding_byte >>= 2;
	}
	return (offset);
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
	if (!set_params(arena, proc))
		proc->instruction = NULL;
	proc->offset = 1 + calc_offset(
								proc->op,
								arena->memory[(proc->pc + 1) % MEM_SIZE]);
}
