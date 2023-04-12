/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 17:58:46 by hgeissle          #+#    #+#             */
/*   Updated: 2023/04/12 14:36:56 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum s_TokenType
{
	TOKEN_COMMAND,
	TOKEN_ARGUMENT,
	TOKEN_REDIRECT_INPUT,
	TOKEN_REDIRECT_OUTPUT,
	TOKEN_PIPE,
	TOKEN_BACKGROUND,
	TOKEN_END
}					t_TokenType;

typedef struct s_Token
{
	t_TokenType		type;
	char			*value;
	int				arg_nb;
	struct s_Token	*prev;
	struct s_Token	*next;
}					t_Token;

typedef struct s_Parse
{
	int				arg_nb;
	t_Dup			*dup;
	char			**cmd;
	struct s_Parse	*next;
}					t_Parse;

typedef struct s_In
{
	int				in;
	struct s_In		*next;
}				t_Dup;

typedef struct s_Out
{
	int				out;
	struct s_Out	*next;
}				t_Out;

#endif