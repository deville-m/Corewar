/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 14:32:19 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/22 10:46:34 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

/*
int	vm_read(void *memory, int pc, void *buffer, size_t size);
int	vm_write(void *memory, int pc, void *buffer, size_t size);
*/

void	trad_input(unsigned char *src, unsigned int *dest, int len)
{
	int	i;
	int	j;

	*dest = 0;
	i = 0;
	j = (len - 1) * 8;
	while (i < len)
	{
		*dest |= src[i];
		if (j > 0)
			*dest <<= j;
		i += 1;
		j -= 8;
	}
}

void	live(t_arena *map, t_process *proc)
{
	int	i;
	unsigned int	value;

	proc->alive += 1;
	i = 0;
	value = proc->params[0].data.direct;
//	trad_input(&(proc->params[0].data.direct[0]), &value, DIR_SIZE);
//	int_input(&(proc->param[0].data.direct[0]), &value);
	value = proc->param[0].data.direct;
	swap_endian(&value, DIR_SIZE);
	while (i < MAX_PLAYERS)
	{
		if (value == map->players[i].id)
			map->players[i].last_live = map->clock;
		i += 1;
	}
}

// je dois determiner s'il s'agit d'un label, si oui aller chercher la donnee et lire
// l'info, comment savoir sa taille ? ->test, sinon, faire le swap endian en fonction de la
// taille et stocker dans l'int du registre ==> pas forcement un int...)

void	ld(t_arena *map, t_process *proc)
{
	unsigned char	buf[4];
	unsigned int	dir;
	short			ind;

	if (proc->params[0].type == INDIRECT)
	{
		ind = proc->params[0].data.indirect;
		swap_endian(&ind, IND_SIZE);
		// je vais lire arbitrairement 4 bytes pour le registre...
		if (vm_read((void *)map->memory, proc->pc + (int)ind, buf, 4) == 4)
		{
			// ici reg est stocke en little endian
//			ft_memcpy(proc->reg[proc->params[1].data.reg_nbr], buf, 4);
			trad_input(buf, &(proc->reg[proc->params[1].data.reg_nbr]), 4);
			swap_endian(&(proc->reg[proc->params[1].data.reg_nbr]), 4);
			proc->carry = 1;
		}
		else
			proc->carry = 0;
	}
	else
	{
		dir = proc->params[0].data.direct;
		swap_endian(&dir, IND_SIZE);
		proc->carry = 1;
	}
}

void	st(t_arena *map, t_process *proc)
{
	int		npc;
	short	ind;

	if (proc->params[1].type == REGISTER)
	{
		npc = proc->pc + ();
			((int)proc->reg[proc->params[1].data.reg_nbr]
		vm_write(map->memory, npc, (void *)&(proc->params[0].data), 4);
	}
	else
	{
		npc = proc->pc + ( % IDX_MOD);
		npc = proc->pc ((int)swap_endian(&(proc->params[1]), IND_SIZE) % IDX_MOD);
		vm_write(map->memory, npc, (void *)&(proc->params[0]), 1);
	}
}
/*
void	add(t_arena *map, t_process *proc)
{
	proc->param[2] = proc->param[0] + proc->param[1];
	proc->carry = 1;
}

// faire un test pour s'assurer que la soustraction est realisee dans ce sens... Rien ne
// le garanti en l'etat
void	sub(t_arena *map, t_process *proc)
{
	proc->param[2] = proc->param[0] - proc->param[1];
	proc->carry = 1;
}

void	and(t_arena *map, t_process *proc)
{
	
}

*/
