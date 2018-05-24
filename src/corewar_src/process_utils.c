/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 16:51:55 by mdeville          #+#    #+#             */
/*   Updated: 2018/05/24 19:11:04 by mdeville         ###   ########.fr       */
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

unsigned int	proc_filter(t_arena *arena)
{
	t_dlist			*walk;
	t_process		*proc;
	unsigned int	total;
	size_t			i;

	ft_dlstfilter(&arena->procs, dead_process, del_process);
	total = 0;
	walk = arena->procs;
	while (walk)
	{
		proc = (t_process *)walk->content;
		total += proc->alive;
		proc->alive = 0;
		walk = walk->next;
	}
	i = 0;
	while (i < arena->np)
	{
		arena->players[i].live_cpt = 0;
		i++;
	}
	return (total);
}

void			exec_processes(t_arena *arena)
{
	t_dlist *walk;

	walk = arena->procs;
	while (walk)
	{
		check_process(arena, walk);
		walk = walk->next;
	}
}
