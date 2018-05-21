/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_instruction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 18:24:08 by mdeville          #+#    #+#             */
/*   Updated: 2018/05/21 16:47:33 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"

int		set_instruction2(t_process *proc, int op_code)
{
	if (op_code == g_op_tab[8].op_code)
		proc->instruction = zjmp;
	else if (op_code == g_op_tab[9].op_code)
		proc->instruction = ldi;
	else if (op_code == g_op_tab[10].op_code)
		proc->instruction = sti;
	else if (op_code == g_op_tab[11].op_code)
		proc->instruction = vm_fork;
	else if (op_code == g_op_tab[12].op_code)
		proc->instruction = lld;
	else if (op_code == g_op_tab[13].op_code)
		proc->instruction = lldi;
	else if (op_code == g_op_tab[14].op_code)
		proc->instruction = lfork;
	else if (op_code == g_op_tab[15].op_code)
		proc->instruction = aff;
	else
		return (0);
	return (1);
}

void	set_instruction(t_process *proc, int op_code)
{
	if (op_code == g_op_tab[0].op_code)
		proc->instruction = live;
	else if (op_code == g_op_tab[1].op_code)
		proc->instruction = ld;
	else if (op_code == g_op_tab[2].op_code)
		proc->instruction = st;
	else if (op_code == g_op_tab[3].op_code)
		proc->instruction = add;
	else if (op_code == g_op_tab[4].op_code)
		proc->instruction = sub;
	else if (op_code == g_op_tab[5].op_code)
		proc->instruction = and;
	else if (op_code == g_op_tab[6].op_code)
		proc->instruction = or;
	else if (op_code == g_op_tab[7].op_code)
		proc->instruction = xor;
	else if (!set_instruction2(proc, op_code))
		proc->instruction = NULL;
}
