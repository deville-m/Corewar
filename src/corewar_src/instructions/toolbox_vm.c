/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox_vm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 11:28:44 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/28 18:08:22 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

short			read_whatever_index(t_process *proc, int nbr)
{
	short	result;

	if (proc->param[nbr].type == REGISTER)
		result = (short)proc->reg[proc->param[nbr].data.reg_nbr];
	else
	{
		result = proc->param[nbr].data.indirect;
		swap_endian(&result, 2);
	}
	return (result);
}

unsigned int	go_read_label(t_arena *map, int npc)
{
	unsigned char	buf[4];
	unsigned int	result;

	vm_read((void *)map->memory, npc, buf, 4);
	trad_input(buf, &result, 4);
	return (result);
}

void			update_carry(t_process *proc, unsigned int a)
{
	if (a == 0)
		proc->carry = 1;
	else
		proc->carry = 0;
}

void			trad_input(unsigned char *src, unsigned int *dest, int len)
{
	int	i;

	*dest = 0;
	i = 0;
	while (i < len)
	{
		*dest |= src[i];
		if (i < len - 1)
			*dest <<= 8;
		i += 1;
	}
}
