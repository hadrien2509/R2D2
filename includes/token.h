/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 17:58:46 by hgeissle          #+#    #+#             */
/*   Updated: 2023/04/19 14:13:45 by hgeissle         ###   ########.fr       */
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
	TOKEN_APPEND_INPUT,
	TOKEN_APPEND_OUTPUT,
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

typedef struct s_Inout
{
	int				fd;
	char			*value;
	struct s_Inout	*prev;
	struct s_Inout	*next;
}				t_Inout;

typedef struct s_Parse
{
	int				arg_nb;
	char			**cmd;
	t_Inout			*in;
	t_Inout			*out;
	struct s_Parse	*next;
}					t_Parse;

#endif
