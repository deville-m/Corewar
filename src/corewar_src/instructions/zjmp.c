/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 13:34:39 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/31 17:29:30 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

void	zjmp(t_arena *map, t_process *proc)
{
	short value;

	(void)map->cycle_to_die;
	value = proc->param[0].data.indirect;
	swap_endian(&value, 2);
	if (proc->carry == 1)
		proc->offset = value % IDX_MOD;
}
