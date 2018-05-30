/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curses2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <iomonad@riseup.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 11:17:44 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/30 09:13:58 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

/*
** @desc Initialise curses librarie
**       and set cleanup callback when
**       exiting.
** @return nil
*/

void				init_curses(void)
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	if (has_colors() == FALSE)
	{
		endwin();
		ft_printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);
	init_pair(6, COLOR_BLACK, COLOR_BLACK);
	init_pair(7, 8, COLOR_BLACK);
	timeout(0);
	atexit((void*)endwin);
}
