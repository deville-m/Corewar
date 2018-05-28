/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 14:15:48 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/28 14:24:04 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	aff(t_arena *map, t_process *proc)
{
	unsigned int	tmp;
	unsigned char	c;

	(void)map->cycle_to_die;
	tmp = proc->reg[proc->param[0].data.reg_nbr];
	c = (unsigned char)(tmp % 256);
	write(1, (void *)&c, 1);
}
