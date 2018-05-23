/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 10:13:40 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/23 15:56:01 by ctrouill         ###   ########.fr       */
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
	t_bool	trash;
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
	unsigned char	exec[CHAMP_MAX_SIZE];		/* Size should be checked before */
	unsigned int	id;
	t_header		header;
	unsigned int	last_live;	/* Derniere fois que le joueur a rapporte en vie */
}					t_player;

/*
** Windows scene structure
*/

typedef struct		s_scene
{
	WINDOW			*memory;
	WINDOW			*sidebar;
	int				key;
}					t_scene;

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
	unsigned int	reg_nbr;
	unsigned int	direct;
	unsigned short	indirect;
};
/*
union				u_data
{
	unsigned char	reg_nbr;
	unsigned char	direct[DIR_SIZE];
	unsigned char	indirect[IND_SIZE];
};
*/
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
	unsigned char	ownership[MEM_SIZE]; /* Index d'appartenance */
	unsigned int	cycle_to_die; /* Periode de verification des processus */
	t_dlist			*procs;	/* Liste des processus */
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
	unsigned int	reg[REG_NUMBER];
	int				pc;			/* Curseur du process */
	t_bool			carry;		/* Carry comme defini dans le sujet */
	unsigned int	alive;		/* Verifie si le processus est en vie | Mis a `false` tous les cycle_to_die */
	unsigned int	wait;		/* temps d'attente en cycle avt proch instru */
	void			(*instruction)(t_arena *, struct s_process *); /* Callback */
	t_op			op; /* instruction parsed according to g_op_tab in op.c */
	t_param			param[MAX_ARGS_NUMBER]; /* Array of parameters */
	int				offset; /* How many bytes to move after instruction exec */
}					t_process;

/*
** @process_utils.c
*/

unsigned int	proc_filter(t_dlist **processes);
void			check_process(t_arena *arena, t_dlist *elem);
void			set_instruction(t_process *proc, int op_code);

/*
** @utils.c
*/

int			vm_read(
					const void *memory,
					int pc,
					void *buffer,
					size_t size);
int			vm_write(
					void *memory,
					int pc,
					void *buffer,
					size_t size);
void		usage(void);
void		dump_memory(const unsigned char *memory,
						const unsigned char *ownership,
						size_t i);
void		dump_player_exec(t_arena *arena);
char*		jcolors(unsigned char owner, t_bool bold);
uint8_t		icolors(unsigned char owner);

/*
** @options
*/

t_bool		parse_options(int argc, char *argv[], struct s_option *opts);

/*
** @kernel.c
*/

t_bool		kernel(struct s_option *options, t_arena *arena);
t_bool		kernel_gfx(struct s_option *options, t_arena *arena);

/*
** @curses.c
*/

void		init_curses(void);
void		apply_windows(t_scene *scene);
void		alloc_window(t_scene *scene);
void		print_status(t_scene *scene, int cycle, int processes);

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

void	init_arena(t_arena *arena, struct s_option *opts);

/*
** @loader.c
*/

t_bool		load_instruction(t_arena *arena,
				t_process *process);


void		swap_endian(void *data, size_t size);

/*
** @live.c (mess)
*/

void		live(t_arena *map, t_process *proc);
void		ld(t_arena *map, t_process *proc);
void		st(t_arena *map, t_process *proc);
void		add(t_arena *map, t_process *proc);
void		sub(t_arena *map, t_process *proc);
void		and(t_arena *map, t_process *proc);
void		or(t_arena *map, t_process *proc);
void		xor(t_arena *map, t_process *proc);

void		lld(t_arena *map, t_process *proc);

void		trad_input(unsigned char *src, unsigned int *dest, int len);

/*
** verbose.c
*/

void		verbose(t_arena *arena, int level);

/*
** @printers
*/

void		print_player_headers(t_arena *arena, size_t i);
void		print_winner(t_arena *arena, size_t i);

/*
** @dump.c
*/

void		dump_cycle_memory(t_scene *scene,
					t_arena *arena);

#endif
