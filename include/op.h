/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2018/05/04 13:29:29 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

# define IND_SIZE				2 // size of value in memory (bytes), also size in parameters
# define REG_SIZE				4 // size of value in memory (bytes), but not in parameters (i.e. it's
								  //     the index of the register which is passed in param)
# define DIR_SIZE				REG_SIZE // size of value in memory (bytes), also size in parameters
										 //     if corresponds to index in param, DIR takes IND_SIZE

# define REG_CODE				1 // encoding byte
# define DIR_CODE				2 // encoding byte
# define IND_CODE				3 // encoding byte

# define MAX_ARGS_NUMBER		4 // ??? VM STUFF
# define MAX_PLAYERS			4 // ??? VM STUFF
# define MEM_SIZE				(4*1024) // Length of memory made by VM
# define IDX_MOD				(MEM_SIZE / 8) // IDX_MOD correspond a la distance max d'ecriture depuis un
												//	opcode donne
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6) // Maximum size of a champion. (?) Might be verified by
											   // verified by VM and/or ASM, for now, we don't know which
											   // one does it.

# define COMMENT_CHAR			'#' // char indicating start of comments
# define LABEL_CHAR				':' // char indicating param is a label (i.e. "%:label_name")
# define DIRECT_CHAR			'%' // char indicating param is direct, without it, it's indirect
# define SEPARATOR_CHAR			',' // separation char of parameters.

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789" // list of char allowed for label names

# define NAME_CMD_STRING		".name" // should be the first part of file, indicating next quoted string is name
											// of max length PROG_NAME_LENGTH
# define COMMENT_CMD_STRING		".comment" // second line, indicating the comment of max length COMMENT_LENGTH

# define REG_NUMBER				16 // number of registers

// VM STUFF
# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

# define INSTRUCTION_SIZE		256 //taille max instruction (?)
# define DESC_SIZE				1024 // ???

/*
** Type of arguments
*/

typedef char	t_arg_type;

# define T_REG					1 // ???
# define T_DIR					2 // ???
# define T_IND					4 // ???
# define T_LAB					8 // ???

/*
** Headers
*/

# define PROG_NAME_LENGTH		(128) // maximum name length
# define COMMENT_LENGTH			(2048) // maximum comment length
# define COREWAR_EXEC_MAGIC		0xea83f3 //needs to be translate into big endian and put into header

typedef struct					s_header
{
	unsigned int				magic;
	char						prog_name[PROG_NAME_LENGTH + 1];
	unsigned int				prog_size;
	char						comment[COMMENT_LENGTH + 1];
}								t_header;

typedef struct					s_op
{
	char						name[INSTRUCTION_SIZE];
	int							nb_param;
	t_arg_type					arg_type[MAX_ARGS_NUMBER];
	char						op_code;
	int							cycle_cost;
	char						desc[DESC_SIZE];
	int							coding_byte;
	int							index;
}								t_op;

extern t_op						g_op_tab[REG_NUMBER + 1];

#endif
