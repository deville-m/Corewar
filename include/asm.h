/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 17:19:14 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/04 20:29:09 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <stdint.h>
# include "op.h"
# include "ft_ctype.h"

# define P_OUTRANGE(x, y) (x < 1 || x > y)

void			stupid_asm(char *in_name);

/*
** @predicate.c
*/

char			is_instruct(const char *line);
t_bool			is_empty(const char *line);
char			is_params_ok(const char opcode,
							const char *params,
							t_bool *status);

/*
** Pseudo tokenizer type
** detemine param type
*/

enum	e_type
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

typedef struct	s_token
{
	enum e_type	type;
	int			line;
	int			column;
	char		*data;
}				t_token;

/*
** @utils.c
*/

uint8_t			arguments_size(const char **args);
uint16_t		operator_tsize(void);

/*
** @lexer.c
*/

t_bool	is_direct(const char *arg);
t_bool	is_indirect(const char *arg);
t_bool	is_label(const char *arg);
t_bool	is_register(const char *arg);

#endif
