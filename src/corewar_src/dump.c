/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomonad <iomonad@riseup.net>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 21:18:42 by iomonad           #+#    #+#             */
/*   Updated: 2018/05/22 21:50:09 by iomonad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

/*
** @desc This is the visual meat.
**       dump to ncurse mem current
**       memory state
** @param mem memory ncurses scene
** @param arena game info structure
** @return nil
*/

static void	apply_memory(WINDOW *mem,
				t_arena *arena)
{
	return ;
}

/*
** @desc Apply infos to the state bar
** @param info side info/bordel scene
** @param arena game info structure
** @return nil
*/

static void apply_sidebar(WINDOW *info,
				t_arena *arena)
{
	return ;
}

/*
** @desc dump current memory to the windows
**       then update the scene.
** @param mem memory ncurses scene
** @param info side info/bordel scene
** @param arena game info structure
** @return nil
*/

void		dump_cycle_memory(WINDOW *mem, WINDOW *info,
					t_arena *arena)
{
	apply_memory(mem, arena);
	apply_sidebar(info, arena);
}
