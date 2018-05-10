/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 09:16:38 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/10 11:55:13 by ctrouill         ###   ########.fr       */
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
	WINDOW *arena;
	WINDOW *status;

	init_curses();
	while (1) {
		windows_borders(arena, status);
	}
	free(arena);
	free(status);
	return (TRUE);
}
