/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 10:13:40 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/11 14:56:40 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

/*
** VM related header file
*/

# include <stdlib.h>
# include <unistd.h>
# include <ncurses.h>
# include <op.h>

# include <libft.h>

struct s_option
{
	size_t	dump;
	size_t	cycles;
	t_bool	gfx;
};

/*
** Players reference using
** `MAX_PLAYERS` defines
*/

typedef struct		s_player
{
	unsigned int	live_cpt;
	unsigned char	exec[CHAMP_MAX_SIZE];
	unsigned int	id;
	t_dlist			*processes;
	t_header		header;
	unsigned int	last_live;
}					t_player;

/*
** Current process structure
** for players tracking
*/

typedef struct		s_process
{
	unsigned int	pc;
	unsigned int	id_player;
	t_bool			carry;
	t_bool			alive;
	unsigned int	wait;		/* temps d'attente en cycle avt proch instru */
	unsigned char	registers[REG_NUMBER][REG_SIZE];
}					t_process;

/*
** Arena structure with
** players and ctx infos
*/

typedef struct		s_arena
{
	unsigned char	arena[MEM_SIZE];
	unsigned int	cycle_to_die;
	t_player		players[MAX_PLAYERS];
	unsigned int	clock;
}					t_arena;

/*
** @utils.c
*/

void		usage(void);

/*
** @options
*/

t_bool		parse_options(int argc, char *argv[], struct s_option *opts);

/*
** @kernel.c
*/

t_bool		kernel(struct s_option *options, t_arena *arena);

/*
** @curses.c
*/

void		init_curses(void);
void		apply_windows(WINDOW *arena, WINDOW *status);
void		alloc_window(WINDOW *arena, WINDOW *status);

/*
** @keybinds
*/

void		keybindinds_callback(int c);

/*
** @checker.c
*/

t_bool		valid_warriors(uint32_t i, char *argv[]);

/*
** @parser.c
*/

t_bool		parseplayers(t_arena *arena,
					char *argv[]);

#endif
