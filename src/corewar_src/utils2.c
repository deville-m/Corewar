/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <iomonad@riseup.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 10:09:41 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/24 13:54:54 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

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
