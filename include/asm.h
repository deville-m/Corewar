/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 17:19:14 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/09 10:57:06 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <stdint.h>
# include "op.h"
# include "ft_ctype.h"
# include "dlst.h"

typedef enum	e_type
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

typedef struct	s_asm_token
{
	enum e_type	type;
	int			line;
	int			column;
	char		*data;
}				t_asm_token;

/*
** @stupid_asm.c
*/

void			stupid_asm(char *in_name);

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

t_dlist *tokenize(int fd);

#endif
