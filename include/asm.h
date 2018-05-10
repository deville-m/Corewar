/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 17:19:14 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/10 18:36:17 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include "libft.h"

typedef enum	e_tok
{
	REG = 1,
	DIR = 2,
	IND = 3,
	LAB = 4,
	SENTINEL
}				t_tok;

enum    e_type
{
	COMMAND_COMMENT = 0,
	COMMAND_NAME,
	STRING,
	LABEL,
	REGISTER,
	DIRECT,
	INDIRECT,
	DIRECT_LABEL,
	INDIRECT_LABEL,
	SEPARATOR,
	INSTRUCTION,
	ENDLINE,
	END
};
/*
** Literal token lexer structure
** for word an syntax processing.
** Meta[t_dlst*]
*/
typedef struct	s_asm_token
{
	enum e_type	type;
	int			line;
	int			column;
	char		*raw;
	int			data;
	int			option;
}				t_asm_token;

typedef struct	s_lab
{
	char		*name;
	int			offset;
	int			instr_offset;
}				t_lab;

typedef struct	s_env
{
	t_header	*header;
	t_list		*tok_head;
	char		*input_name;
	t_list		*lab_h;
	t_list		*to_do;
	int			fd;
}				t_env;


/*
** @stupid_asm.c
*/

void			stupid_asm(t_env *env, char *in_name);
void			bug_err(char *mess);

/*
** @predicate.c
*/

char			is_instruct(const char *line);
t_bool			is_empty(const char *line);
unsigned char	craft_op_byte(const char opcode,
							  const char *params,
							  t_bool *status);
/*
** @rules.c
*/

void			transpose(t_tok *transpose,
						  const char **split,
						  char opcode,
						  uint8_t i);
t_tok			tokenize(const char *occur);
t_bool			check_rules(const char opcode,
							t_tok *transpose,
							uint8_t i);

/*
** @utils.c
*/

uint8_t			arguments_size(const char **args);
uint16_t		operator_tsize(void);

/*
** @lexer.c
*/

t_bool			is_direct(const char *arg);
t_bool			is_indirect(const char *arg);
t_bool			is_label(const char *arg);
t_bool			is_register(const char *arg);

/*
** @collision.c
*/

t_bool			check_collisions(uint_fast32_t i);

/*
** @stupid_analyser.c
*/
void	create_token(t_env *env, enum e_type type, int line, int column, char *raw, int data, int option);
void	ft_lstinsert(t_list **head, void *content, int content_size);

/*
** @analyser.c
*/
int		craft_directs(t_env *env, int fd);
int		oh_a_comment_pass_it(int fd);

/*
** @output.c
*/
int		craft_file(t_env *env);

/*
** @crafting_tools.c
*/


/*
** @create_output_file.c
*/
int		create_output_file(t_env *env);

/*
** @toolbox.c
*/
void	swap_endian(void *data, size_t size);

#endif
