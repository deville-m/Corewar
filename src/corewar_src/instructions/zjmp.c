/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 13:34:39 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/22 16:58:52 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

void	zjmp(t_arena *map, t_process *proc)
{
	if (proc->carry == 1)
		proc->offset = proc->pc + (int)proc->param[0].data.indirect;
}
