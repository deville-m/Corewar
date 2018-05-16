/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 10:13:40 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/16 16:51:28 by mdeville         ###   ########.fr       */
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
# include <colors.h>

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
	unsigned int	live_cpt;	/* Nombre de fois rapporte en vie [Inc] */
	unsigned char	*exec;		/* Size should be checked before */
	unsigned int	id;
	t_header		header;
	unsigned int	last_live;	/* Derniere fois que le joueur a rapporte en vie */
}					t_player;

/*
** instruction enum type
*/

enum				e_type
{
	INDIRECT = 0,
	DIRECT,
	REGISTER
};

/*
** Parameter structs
** TODO: write docs
*/

union				u_data
{
	unsigned char	reg_nbr;
	unsigned char	direct[DIR_SIZE];
	unsigned char	indirect[IND_SIZE];
};

typedef struct		s_param
{
	enum e_type		type;
	union u_data	data;
}					t_param;

/*
** Arena structure with
** players and ctx infos
*/

typedef struct		s_arena
{
	unsigned char	memory[MEM_SIZE]; /* Plage de memoire */
	unsigned int	ownership[MEM_SIZE]; /* Index d'appartenance */
	unsigned int	cycle_to_die; /* Periode de verification des processus */
	t_dlist			*processes;	/* Liste des processus */
	t_player		players[MAX_PLAYERS];
	unsigned short	np;			/* Current player numbers */
	unsigned int	clock;		/* Compteur general de cycle */
}					t_arena;

/*
** Current process structure
** for players tracking
*/

typedef struct		s_process
{
	unsigned char	registers[REG_NUMBER][REG_SIZE];
	int				pc;			/* Curseur du process */
	t_bool			carry;		/* Carry comme defini dans le sujet */
	t_bool			alive;		/* Verifie si le processus est en vie | Mis a `false` tous les cycle_to_die */
	unsigned int	wait;		/* temps d'attente en cycle avt proch instru */
	void			(*instruction)(t_arena *, struct s_process *); /* Callback */
	t_op			op; /* instruction parsed according to g_op_tab in op.c */
	t_param			params[MAX_ARGS_NUMBER]; /* Array of parameters */
	int				offset; /* How many bytes to move after instruction exec */
}					t_process;

/*
** @utils.c
*/

void		usage(void);
void		dump_memory(const unsigned char *memory,
				size_t i);
void		dump_player_exec(t_arena *arena);

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
						 char *argv[],
						 size_t i);

/*
** @init.c
*/
void		init_arena(t_arena *arena);

/*
** loader.c
*/

t_bool	load_instruction(t_arena *arena,
				t_process *process);

#endif
