/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 13:50:28 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/29 20:09:50 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_fork(t_arena *map, t_process *proc)
{
	t_process	*new;
	t_dlist		*tmp;
	short		ind;

	tmp = ft_dlstnew((void *)proc, sizeof(t_process));
	if (!tmp)
		return ;
	ft_dlstprepend(&(map->procs), tmp);
	new = (t_process *)map->procs->content;
	new->wait = proc->wait + 1;
	new->instruction = NULL;
	ind = proc->param[0].data.indirect;
	swap_endian(&ind, 2);
	new->offset = (int)(ind % IDX_MOD);
}
