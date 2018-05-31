/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:22:21 by mdeville          #+#    #+#             */
/*   Updated: 2018/05/31 17:59:40 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "ft_printf.h"

void		verbose(t_arena *arena, int level)
{
	if (level & V_CLOCK)
		ft_printf("----------It is now cycle %6u----------\n", arena->clock);
	if (level & V_ALL)
	{
		ft_printf("Processes: %3u  |  Cycle to die: %6d\n",
				ft_dlstlen(arena->procs), arena->cycle_to_die);
	}
}
