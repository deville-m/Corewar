/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 17:19:14 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/07 17:49:43 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include <libft.h>

# define P_OUTRANGE(x, y) (x < 1 || x > y)
# define ASSERT(x) (if (!(x)) ft_prinf("Assertion \"%s\" at l%d.", x, __LINE__))


typedef struct	s_env
{
	t_list	*tok_head;
	char	*input_name; //Corresponds to the .s filename, in order to craft the .cor
}				t_env;

void			stupid_asm(t_env *env, char *in_name);
void			bug_err(char *mess);
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

typedef struct	s_ltoken
{
	enum e_type	type;
	int			line;
	int			column;
	char		*raw;
	int			data;
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

/*
** @stupid_analyser.c
*/
int		create_token(t_env *env, enum e_type type, int line, int column, char *raw);

/*
** @analyser.c
*/
int		craft_directs(t_env *env, int fd);
int		oh_a_comment_pass_it(int fd);

#endif
