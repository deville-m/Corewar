/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 17:19:14 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/07 16:04:21 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <stdint.h>
# include "op.h"
# include "ft_ctype.h"
# include "dlst.h"


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

typedef struct	s_asm_token
{
	enum e_type	type;
	int			line;
	int			column;
	char		*data;
}				t_asm_token;

t_dlist *tokenize(int fd);

#endif
