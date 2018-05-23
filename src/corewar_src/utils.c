/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 15:20:10 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/23 16:07:37 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <libft.h>
#include <colors.h>
#include <commons.h>

int			vm_read(const void *memory, int pc, void *buffer, size_t size)
{
	unsigned char	*smem;
	unsigned char	*sbuf;
	size_t			i;

	if (!memory || !buffer)
		return (-1);
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

int			vm_write(void *memory, int pc, void *buffer, size_t size)
{
	unsigned char	*smem;
	unsigned char	*sbuf;
	size_t			i;

	if (!memory || !buffer)
		return (-1);
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
	ft_printf("    -d <nbr_cycle> :: Int\n");
	ft_printf("    -n <number>    :: Int\n");
	ft_printf("    -x             # Ncurses output\n");
	ft_printf("    -t             # Dump loader init to stdout\n");
	exit(EXIT_FAILURE);
}

/*
 * Retrieve ad-hoc colors depending
 * of the player cusor.
 */
char*	jcolors(unsigned char owner, t_bool bold)
{
	if (owner == 0xFF) {
		return ((bold) ? LIGHTGREEN : GREEN);
	} else if (owner == 0xFE) {
		return ((bold) ? LIGHTBLUE : BLUE);
	} else if (owner == 0xFD) {
		return ((bold) ? LIGHTRED : RED);
	} else if (owner == 0xFC) {
		return ((bold) ? LIGHTYELLOW : YELLOW);
	}
	return ((bold) ? LIGHTBLACK : BLACK);
}

uint8_t	icolors(unsigned char owner)
{
	if (owner == 0xFF) {
		return (1);
	} else if (owner == 0xFE) {
		return (2);
	} else if (owner == 0xFD) {
		return (3);
	} else if (owner == 0xFC) {
		return (4);
	}
	return (5);
}

/*
** @desc dump memory to stdout
** @return nil
*/

void			dump_memory(const unsigned char *memory,
							const unsigned char *ownership,
							size_t i)
{
	ft_printf("Dumping memory of size: %d\n", MEM_SIZE);
	while (i < MEM_SIZE)
	{
		if (memory[i] == 0xff)
			ft_putstr(jcolors(ownership[i], FALSE));
		else if (memory[i] == 0x00)
			ft_putstr(jcolors(ownership[i], FALSE));
		else
			ft_putstr(jcolors(ownership[i], TRUE));
		if ((i % 50) == 0)
			ft_putchar('\n');
		ft_printf("%.2x ", memory[i]);
		i++;
	}
	ft_putchar('\n');
	ft_putstr(RESET);
}

/*
** @desc Dump player exec to stdout
** @return nil
*/

void		dump_player_exec(t_arena *arena)
{
	size_t	p;
	size_t	i;

	p = 0;
	while (p < arena->np)
	{
		i = 0;
		ft_printf("\nSize of player[%zu]: %u\n", p,
			arena->players[p].header.prog_size);
		while (i < arena->players[p].header.prog_size)
		{
			if (arena->players[p].exec[i] != 0x0)
				ft_putstr(LIGHTRED);
			else
				ft_putstr(BLACK);
			if ((i % 15) == 0)
				ft_putchar('\n');
			ft_printf("\\x%.2x ", arena->players[p].exec[i]);
			i++;
		}
		ft_printf("\n%s", RESET);
		p++;
	}
}
