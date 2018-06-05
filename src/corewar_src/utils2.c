/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <iomonad@riseup.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 10:09:41 by ctrouill          #+#    #+#             */
/*   Updated: 2018/06/04 18:55:02 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

int			own_write(void *memory, int pc, unsigned char owner, size_t size)
{
	unsigned char	*sbuf;
	size_t			i;

	if (!memory)
		return (-1);
	pc = pc % MEM_SIZE;
	if (pc < 0)
		pc = MEM_SIZE + pc;
	sbuf = (unsigned char *)memory;
	i = 0;
	while (i < size)
	{
		sbuf[pc % MEM_SIZE] = owner;
		++pc;
		++i;
	}
	return (i);
}

/*
** @desc TODO
** @return TODO
*/

int			vm_read(const void *memory, int pc, void *buffer, size_t size)
{
	unsigned char	*smem;
	unsigned char	*sbuf;
	size_t			i;

	if (memory == NULL || buffer == NULL)
		return (-1);
	pc = pc % MEM_SIZE;
	if (pc < 0)
		pc = MEM_SIZE + pc;
	sbuf = (unsigned char *)buffer;
	smem = (unsigned char *)memory;
	i = 0;
	while (i < size)
	{
		sbuf[i] = smem[pc % MEM_SIZE];
		++i;
		++pc;
	}
	return (i);
}

/*
** @desc TODO
** @return TODO
*/

int			vm_write(void *memory, int pc, void *buffer, size_t size)
{
	unsigned char	*smem;
	unsigned char	*sbuf;
	size_t			i;

	if (memory == NULL || buffer == NULL)
		return (-1);
	pc = pc % MEM_SIZE;
	if (pc < 0)
		pc = MEM_SIZE + pc;
	sbuf = (unsigned char *)buffer;
	smem = (unsigned char *)memory;
	i = 0;
	while (i < size)
	{
		smem[pc % MEM_SIZE] = sbuf[i];
		++i;
		++pc;
	}
	return (i);
}

/*
** @desc print usage and exit;
** @return Nil (exit)
*/

void		usage(void)
{
	ft_printf("Usage: ./corewar [OPTS] championXX.cor <...>\n");
	ft_printf("where options include:\n");
	ft_printf("    -d <nbr_cycle> :: UInt\n");
	ft_printf("    -n <player_id> :: UInt\n");
	ft_printf("    -v <verbose>   :: Can be OR'd\n");
	ft_printf("         %d  # Aff and Live\n", V_BASIC);
	ft_printf("         %d  # Clock counter\n", V_CLOCK);
	ft_printf("         %d  # Death events\n", V_DEATH);
	ft_printf("         %d  # Instruction events\n", V_OP);
	ft_printf("         %d # Environnement\n", V_ALL);
	ft_printf("    -x             # Ncurses output\n");
	ft_printf("    -t             # Dump loader init to stdout\n");
	ft_printf("    -a             # Enable audio experience\n");
	exit(EXIT_FAILURE);
}
