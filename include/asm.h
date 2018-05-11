/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 17:19:14 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/11 18:21:09 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <stdint.h>
# include "op.h"
# include "ft_ctype.h"
# include "dlst.h"
# include "libft.h"

enum			e_type
{
	COMMAND_COMMENT = 0,
	COMMAND_NAME = 1,
	STRING = 2,
	LABEL = 3,
	REGISTER = 4,
	DIRECT = 5,
	INDIRECT = 6,
	DIRECT_LABEL = 7,
	INDIRECT_LABEL = 8,
	SEPARATOR = 9,
	INSTRUCTION = 10,
	ENDLINE = 11,
	END = 12
};

typedef enum	e_tok
{
	REG = 1,
	DIR = 2,
	IND = 3,
	LAB = 4,
	SENTINEL
}				t_tok;

typedef struct	s_asm_token
{
	enum e_type	type;
	int			line;
	int			column;
	char		*raw;
	int			data;
	t_bool		option;
}				t_asm_token;

/*
** Literal token lexer structure
** for word an syntax processing.
** Meta[t_dlst*]
*/

typedef struct	s_env
{
	t_header	*header;
	t_list		*tok_head;
	char		*input_name;
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
t_tok			tokenize_args(const char *occur);
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

size_t			is_direct(const char *arg);
size_t			is_indirect(const char *arg);
size_t			is_label(const char *arg);
size_t			is_register(const char *arg);
size_t			is_comment(const char *arg);
size_t			is_name(const char *arg);
size_t			is_indirect_label(const char *arg);
size_t			is_direct_label(const char *arg);
size_t			is_string(const char *arg, t_asm_token *token);
size_t			is_instruction(const char *arg);
size_t			is_separator(const char *arg);

/*
** @collision.c
*/

t_bool			check_collisions(const char	*base,
								const char	*labels,
								const char  *n_cmd,
								const char  *c_cmd);

/*
** @stupid_analyser.c
*/

int				create_token(t_env *env, enum e_type type, int line,
					int column, char *raw);

/*
** @analyser.c
*/

int				craft_directs(t_env *env, int fd);
int				oh_a_comment_pass_it(int fd);

/*
** @tokenize.c
*/

t_asm_token		*get_token(t_dlist *elem);
t_bool			multiline_string(const char *line);
t_dlist			*tokenize(int fd);
void			print_tokens(t_dlist *elem);

t_dlist			*check_instruction(t_dlist *lst);
void			syntax_check(t_dlist *tokens);
void			syntax_error(char *message, t_asm_token *token);


#endif
