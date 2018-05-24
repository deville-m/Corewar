/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 13:34:39 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/24 18:00:19 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

void	zjmp(t_arena *map, t_process *proc)
{
	short value;

	value = proc->param[0].data.direct;
	swap_endian(&value, sizeof(value));
	if (proc->carry == 1)
		proc->offset = value;
}
