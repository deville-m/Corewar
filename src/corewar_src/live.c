/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 14:32:19 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/22 10:29:56 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

/*
int	vm_read(void *memory, int pc, void *buffer, size_t size);
int	vm_write(void *memory, int pc, void *buffer, size_t size);
*/

void	short_input(unsigned char *src, unsigned short *dest)
{
	*dest = 0;
	*dest |= src[0];
	*dest <<= 2;
	*dest |= src[1];
}

void	int_input(unsigned char *src, unsigned int *dest)
{
	*dest = 0;
	*dest |= src[0];
	*dest <<= 6;
	*dest |= src[1];
	*dest <<= 4;
	*dest |= src[2];
	*dest <<= 2;
	*dest |= src[3];
}

void	live(t_arena *map, t_process *proc)
{
	int	i;
	unsigned int	value;

	proc->alive += 1;
	i = 0;
	//int_input(&(proc->param[0].data.direct[0]), &value);
	swap_endian(&value, DIR_SIZE);
	while (i < MAX_PLAYERS)
	{
		if (value == map->players[i].id)
			map->players[i].last_live = map->clock;
		i += 1;
	}
}
/*
void	ld(t_arena *map, t_process *proc)
{
	void	*tmp;

// je dois determiner s'il s'agit d'un label, si oui aller chercher la donnee et lire
// l'info, comment savoir sa taille ? ->test, sinon, faire le swap endian en fonction de la
// taille et stocker dans l'int du registre...)
// determinger si nous devons stocker en little ou big endian dans les reg
	if (vm_read(map->memory, , tmp, 1) > 0)
	{

		proc->carry = 1;
	}
	else
		proc->carry = 0;

	proc->param[1] = swap_endian(proc->param[0], sizeof(proc->param[0]));
}

void	st(t_arena *map, t_process *proc)
{
	int	new_pc;

	if (sizeof(proc->param[1]) == 1)
	{
		new_pc = proc->pc + ((int)proc->param[1] % IDX_MOD);
		vm_write(map->memory, new_pc, (void *)&(proc->param[0]), 1); //map->memory ??
	}
	else
	{
		new->pc = proc->pc ((int)swap_endian(&(proc->param[1]), IND_SIZE) % IDX_MOD);
		vm_write(map->memory, new_pc, (void *)&(proc->param[0]), 1); //map->memory ??
	}
}

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
