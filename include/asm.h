/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 17:19:14 by rbaraud           #+#    #+#             */
/*   Updated: 2018/06/04 15:33:04 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <stdint.h>
# include "op.h"
# include "ft_ctype.h"
# include "dlst.h"
# include "lst.h"
# include "commons.h"
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
	t_list		*lab_h;
	t_list		*to_do;
	int			fd;
}				t_env;

typedef struct	s_lab
{
	char		*name;
	int			offset;
	int			instr_offset;
}				t_lab;

/*
** @predicate.c
*/

char			is_instruct(const char *line);
t_bool			is_empty(const char *line);
unsigned char	craft_op_byte(
							const char opcode,
							const char *params,
							t_bool *status);

/*
** @rules.c
*/

void			transpose(
							t_tok *transpose,
							const char **split,
							char opcode,
							uint8_t i);
t_tok			tokenize_args(const char *occur);
t_bool			check_rules(
							const char opcode,
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
size_t			is_string(const char *arg);
size_t			is_instruction(const char *arg);
size_t			is_separator(const char *arg);

/*
** @collision.c
*/

t_bool			check_collisions(const char	*base,
								const char	*labels,
								const char	*n_cmd,
								const char	*c_cmd);

/*
** @tokenize.c
*/

void			update_token(t_asm_token *token);
void			print_tokens(t_dlist *elem);
t_asm_token		*get_token(t_dlist *elem);
t_bool			multiline_string(const char *line);
t_dlist			*tokenize(int fd);
void			print_tokens(t_dlist *elem);

int				filter_token(t_dlist *elem);
void			del_token(void *content, size_t content_size);
t_dlist			*check_instruction(t_dlist *lst);
void			check_labels(t_dlist *tokens);
t_dlist			*syntax_check(t_dlist *tokens);
void			syntax_error(char *message, t_asm_token *token);

/*
** @craft_out.c
*/

int				craft_file(t_env *env);

/*
** @crafting.c
*/
intmax_t		craft_prog(t_env *env, t_list *tmp);

/*
** @crafting_tools.c
*/

t_lab			*new_t_lab(char *name, int offset, int instr_offset);
t_lab			*is_labelled(t_env *env, t_asm_token *tok);
void			add_lab_elem(t_env *env, t_asm_token *tok, int offset);

/*
** @create_output_file.c
*/
int				create_output_file(t_env *env);

/*
** @toolbox.c
*/
void			ft_lstinsert(t_list **head, void *content, int content_size);
void			bug_err(char *mess);

#endif
