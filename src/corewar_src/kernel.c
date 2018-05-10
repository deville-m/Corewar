/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 09:16:38 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/10 12:27:18 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

/*
** @desc monothilic part of the arena
** @param options retrieved
** @return nil
*/

t_bool		kernel(struct s_option *options)
{
	WINDOW *arena = NULL;
	WINDOW *status = NULL;

	init_curses();
	while (1)
	{
		apply_windows(arena, status);
		free(arena);
		free(status);
	}
	return (TRUE);
}
