/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2018/06/05 17:44:09 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

# define IND_SIZE				2
# define REG_SIZE				4

# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)

# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHARS			"#;"
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

/*
** Type of arguments
*/

typedef char	t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

/*
** Headers
*/

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct					s_header
{
	unsigned int				magic;
	char						prog_name[PROG_NAME_LENGTH + 1];
	unsigned int				prog_size;
	char						comment[COMMENT_LENGTH + 1];
}								t_header;

/*
** Perso
*/

# define EOL '\n'
# define WHITESPACE "\t "
# define MINUS '-'
# define REGISTER_CHAR 'r'
# define BASE "0123456789"
# define STRING_CHAR '"'

# define INSTRUCTION_NBR 16
# define INSTRUCTION_SIZE		256
# define DESC_SIZE				1024

/*
** No_token: COMMENT_CHAR -> EOL
**
** + STRING (")
** + SEPARATOR (,)
** + ENDLINE (\n)
**
** + DIRECT (%)
** + DIRECT_LABEL (%:)
** + REGISTER (REGISTER_CHAR + number inside BASE)
**
** + INDIRECT (suite chiffres appartenant a BASE)
**
** INDIRECT_LABEL (':' puis label_name)
**
** COMMAND_COMMENT (.comment)
** COMMAND_NAME (.name)
**
** + LABEL (LABEL_CHARS termine par :)
**
** + INSTRUCTION (chaine de LABEL_CHARS)
**
** + END ((null)) serait juste une erreur ? Ou NULL representera end... PFFFF
*/

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
	int							carry;
}								t_op;

extern t_op						g_op_tab[INSTRUCTION_NBR];

#endif
