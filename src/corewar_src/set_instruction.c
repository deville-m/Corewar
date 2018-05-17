/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_instruction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 18:24:08 by mdeville          #+#    #+#             */
/*   Updated: 2018/05/17 18:29:14 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"

void	set_instruction(t_process *proc, int op_code)
{
	if (op_code == g_op_tab[0].op_code)
		proc->instruction = live;
	else if (op_code == g_op_tab[1].op_code)
		proc->instruction = ;
	else if (op_code == g_op_tab[1].op_code)
		proc->instruction = ;
	else if (op_code == g_op_tab[1].op_code)
		proc->instruction = ;
	else if (op_code == g_op_tab[1].op_code)
		proc->instruction = ;
	else if (op_code == g_op_tab[1].op_code)
		proc->instruction = ;
	else if (op_code == g_op_tab[1].op_code)
		proc->instruction = ;
	else if (op_code == g_op_tab[1].op_code)
		proc->instruction = ;
	else if (op_code == g_op_tab[1].op_code)
		proc->instruction = ;
}
