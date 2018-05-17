/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 16:51:55 by mdeville          #+#    #+#             */
/*   Updated: 2018/05/17 17:25:10 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "dlst.h"

static void		del_process(void *content, size_t content_size)
{
	(void)content_size;
	free(content);
}

static int		dead_process(t_dlist *elem)
{
	t_process *proc;

	proc = (t_process *)elem->content;
	if (proc->alive == FALSE)
		return (0);
	else
		return (1);
}

unsigned int	proc_filter(t_dlist **processes)
{
	t_dlist			*walk;
	t_process		*proc;
	unsigned int	total;

	ft_dlstfilter(processes, dead_process, del_process);
	total = 0;
	walk = *processes;
	while (walk)
	{
		proc = (t_process *)walk->content;
		total += proc->alive;
		proc->alive = 0;
		walk = walk->next;
	}
	return (total);
}

void			exec_processes(t_arena *arena)
{
	t_dlist *walk;

	walk = arena->processes;
	while (walk)
	{
		check_process(arena, walk);
		walk = walk->next;
	}
}
