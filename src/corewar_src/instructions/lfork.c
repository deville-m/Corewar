/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 14:14:25 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/30 16:55:12 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	lfork(t_arena *map, t_process *proc)
{
	t_process	*new;
	t_dlist		*tmp;
	short		ind;

	tmp = ft_dlstnew((void *)proc, sizeof(t_process));
	if (!tmp)
		return ;
	ft_dlstprepend(&(map->procs), tmp);
	new = (t_process *)map->procs->content;
	new->wait = map->clock + 1;
	new->instruction = NULL;
	ind = proc->param[0].data.indirect;
	swap_endian(&ind, 2);
	new->offset = (int)ind;
}
