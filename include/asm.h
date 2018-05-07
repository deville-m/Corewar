/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 17:19:14 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/07 09:49:22 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include <libft.h>

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

typedef enum	e_tok
{
	REG = 1,
	DIR = 2,
	IND = 3,
	LAB = 4,
	SENTINEL
}				t_tok;

typedef struct	s_ltoken
{
	enum e_tok	type;
	int			line;
	int			column;
	char		*data;
}				t_ltoken;

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
