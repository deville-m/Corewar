/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 10:13:40 by ctrouill          #+#    #+#             */
/*   Updated: 2018/06/04 18:53:12 by ctrouill         ###   ########.fr       */
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

# define MAX_SPEED 1
# define MIN_SPEED 50000
# define STEP_SPEED 5000

# define V_BASIC 1
# define V_CLOCK 2
# define V_DEATH 4
# define V_OP    8
# define V_ALL   16

struct				s_option
{
	unsigned int	dump;
	unsigned int	verbose;
	size_t			cycles;
	t_bool			gfx;
	int				ids[MAX_PLAYERS];
	t_bool			ids_activated;
	t_bool			audio;
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
	t_header		header;
	unsigned int	last_live;
}					t_player;

/*
** Windows scene structure
*/

typedef struct		s_scene
{
	WINDOW			*memory;
	WINDOW			*sidebar;
	int				key;
	long long int	speed;
	t_bool			pause;
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
	unsigned char	reg_nbr;
	unsigned int	direct;
	unsigned short	indirect;
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
	unsigned char	memory[MEM_SIZE];
	unsigned char	ownership[MEM_SIZE];
	int				cycle_to_die;
	t_dlist			*procs;
	t_player		players[MAX_PLAYERS];
	unsigned short	np;
	unsigned int	clock;
	struct s_option	*opts;
}					t_arena;

/*
** Current process structure
** for players tracking
*/

typedef struct		s_process
{
	unsigned int	reg[REG_NUMBER + 1];
	int				pc;
	t_bool			carry;
	unsigned int	alive;
	unsigned int	wait;
	void			(*instruction)(t_arena *, struct s_process *);
	t_op			op;
	t_param			param[MAX_ARGS_NUMBER];
	int				offset;
}					t_process;

/*
** @process_utils.c
*/

unsigned int		proc_filter(t_arena *arena);
t_bool				set_op(unsigned char op_code, t_op *op);
void				check_process(t_arena *arena, t_dlist *elem);
void				set_instruction(t_process *proc, int op_code);

/*
** @utils.c
*/

int					own_write(
				void *memory,
				int pc,
				unsigned char owner,
				size_t size);
int					vm_read(const void *memory,
				int pc,
				void *buffer,
				size_t size);
int					vm_write(void *memory,
				int pc,
				void *buffer,
				size_t size);
void				usage(void);
void				dump_memory(const unsigned char *memory,
						const unsigned char *ownership,
						size_t i);
void				dump_player_exec(t_arena *arena);
char				*jcolors(unsigned char owner, t_bool bold);
uint8_t				icolors(unsigned char owner, t_arena *arena);

/*
** @options
*/

t_bool				parse_options(int argc, char *argv[],
						struct s_option *opts);

/*
** @kernel.c
*/

t_bool				kernel(struct s_option *options, t_arena *arena);
t_bool				kernel_gfx(struct s_option *options, t_arena *arena);

/*
** @curses.c
*/

void				init_curses(void);
void				apply_windows(t_scene *scene, t_arena *arena);
void				alloc_window(t_scene *scene, t_arena *arena);
void				print_status(t_scene *scene, int cycle,
						int processes, t_arena *arena);

/*
** @keybinds
*/

void				keybindinds_callback(char c, t_scene *scene);

/*
** @checker.c
*/

t_bool				valid_warriors(uint32_t i, char *argv[]);
t_bool				check_magic(int fd);

/*
** @parser.c
*/

t_bool				parseplayers(t_arena *arena,
				char *argv[],
				size_t i,
				struct s_option *opts);

/*
** @init.c
*/

void				init_arena(t_arena *arena, struct s_option *opts);

/*
** @loader.c
*/

t_bool				load_instruction(t_arena *arena,
				t_process *process);
void				swap_endian(void *data, size_t size);

/*
** @live.c (mess)
*/

void				live(t_arena *map, t_process *proc);
void				ld(t_arena *map, t_process *proc);
void				st(t_arena *map, t_process *proc);
void				add(t_arena *map, t_process *proc);
void				sub(t_arena *map, t_process *proc);
void				and(t_arena *map, t_process *proc);
void				or(t_arena *map, t_process *proc);
void				xor(t_arena *map, t_process *proc);
void				zjmp(t_arena *map, t_process *proc);

void				ldi(t_arena *map, t_process *proc);
void				sti(t_arena *map, t_process *proc);
void				vm_fork(t_arena *map, t_process *proc);

void				lld(t_arena *map, t_process *proc);

void				lldi(t_arena *map, t_process *proc);
void				lfork(t_arena *map, t_process *proc);
void				aff(t_arena *map, t_process *proc);

unsigned int		go_read_label(t_arena *map, int npc);
void				trad_input(unsigned char *src, unsigned int *dest, int len);
void				update_carry(t_process *proc, unsigned int a);
short				read_whatever_index(t_arena *map, t_process *proc, int nbr);

/*
** verbose.c
*/

void				verbose(t_arena *arena, int level);

/*
** @printers
*/

void				print_player_headers(t_arena *arena, size_t i);
void				print_winner(t_arena *arena, size_t i);
void				print_winner_gfx(t_arena *arena, size_t i,
							t_scene *scn, size_t f);

/*
** @dump.c
*/

void				print_exec(t_arena *arena, t_process *process);
void				dump_cycle_memory(t_scene *scene,
							t_arena *arena);
t_bool				player_ownership(unsigned int player, t_arena *arena);
void				init_values(size_t *i, int *xx, int *yy);
t_bool				apply_pc(t_arena *arena, int i);
void				shut_up_and_take_my_memory(t_arena *arena);

/*
** @sound.c
*/

void				play_voice(const char *message);
void				play_sound(const char *file);

#endif
