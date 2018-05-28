/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 13:50:28 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/28 14:45:59 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_fork(t_arena *map, t_process *proc)
{
	t_process	*new;
	t_dlist		*tmp;
	int			i;

	tmp = ft_dlstnew((void *)proc, sizeof(t_process));
	if (!tmp)
		return ;
	ft_dlstprepend(&(map->procs), tmp);
	new = (t_process *)map->procs->content;
	i = 0;
	while (i++ <= REG_NUMBER)
		new->reg[i] = proc->reg[i];
	new->pc = proc->pc;
	new->carry = proc->carry;
	new->alive = proc->alive;
	new->wait = proc->wait;
	new->instruction = NULL;
	new->offset = (int)proc->param[0].data.direct % IDX_MOD;
}
