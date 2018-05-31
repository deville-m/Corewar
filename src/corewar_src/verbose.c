/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:22:21 by mdeville          #+#    #+#             */
/*   Updated: 2018/05/30 18:58:36 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "ft_printf.h"

static void	instruction(t_dlist *elem)
{
	t_process		*proc;
	int				i;

	proc = (t_process *)elem->content;
	if (!proc->instruction)
		ft_printf("Missing Instruction\n");
	else
	{
		i = 0;
		ft_printf("Executing %s ; %d | ", proc->op.name, proc->wait);
		while (i < proc->op.nb_param - 1)
			ft_printf("%#x, ", proc->param[i++].data);
		ft_printf("%#x\n", proc->param[i].data);
	}
}

static void	instruction_pc(t_dlist *elem)
{
	t_process		*proc;
	int				i;

	proc = (t_process *)elem->content;
	if (!proc->instruction)
		ft_printf("Missing Instruction\n");
	else
	{
		i = 0;
		ft_printf("Executing %s ; %d - ", proc->op.name, proc->wait);
		while (i < proc->op.nb_param - 1)
			ft_printf("%#x, ", proc->param[i++].data);
		ft_printf("%#x   |   ", proc->param[i].data);
	}
	ft_printf("PC: %d - Offset: %d\n", proc->pc, proc->offset);
}

void		verbose(t_arena *arena, int level)
{
	if (level == 0)
		return ;
	if (level >= 1)
		ft_printf("-------------------------\nIt's now cycle %u\n", arena->clock);
	if (level == 2)
		ft_dlstiter(arena->procs, instruction);
	if (level >= 3)
		ft_dlstiter(arena->procs, instruction_pc);
}
