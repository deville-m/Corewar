/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 15:20:10 by ctrouill          #+#    #+#             */
/*   Updated: 2018/06/04 19:22:33 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <libft.h>
#include <colors.h>
#include <commons.h>

/*
** @desc dump memory to stdout
** @return nil
*/

void			dump_memory(const unsigned char *memory,
						const unsigned char *ownership,
						size_t i)
{
	(void)ownership;
	ft_printf("0x0%.3x : ", i);
	ft_printf("%.2x ", memory[i++]);
	while (i < MEM_SIZE)
	{
		if ((i + 1) != MEM_SIZE && (i % 64) == 0)
			ft_printf("\n0x0%.3x : ", i);
		else if ((i % 64) == 0)
			ft_putchar('\n');
		ft_printf("%.2x ", memory[i]);
		i++;
	}
	ft_putchar('\n');
}

void			print_exec(t_arena *arena, t_process *proc)
{
	int i;

	if (proc->op.coding_byte)
		ft_printf("Exec %s at %#.3x with encoding_byte %#.8hhb and param ",
				proc->op.name,
				proc->pc,
				arena->memory[(proc->pc + 1) % MEM_SIZE]);
	else
		ft_printf("Exec %s at %#.3x and param ",
				proc->op.name,
				proc->pc,
				arena->memory[(proc->pc + 1) % MEM_SIZE]);
	i = 0;
	while (i < proc->op.nb_param)
	{
		if (proc->param[i].type == REGISTER)
			ft_printf("r%.2hhu -- > %#.8x | ", proc->param[i].data.reg_nbr,
					proc->reg[proc->param[i].data.reg_nbr]);
		else if (proc->param[i].type == DIRECT)
			ft_printf("%#.4hx | ", proc->param[i].data.indirect);
		else
			ft_printf("%#.8x | ", proc->param[i].data.direct);
		i++;
	}
	write(1, "\n", 1);
}
