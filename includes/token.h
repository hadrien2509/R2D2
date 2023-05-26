/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 17:58:46 by hgeissle          #+#    #+#             */
/*   Updated: 2023/05/26 17:57:32 by hgeissle         ###   ########.fr       */
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
}					t_tokenType;

typedef struct s_Token
{
	t_tokenType		type;
	char			*value;
	int				arg_nb;
	struct s_Token	*prev;
	struct s_Token	*next;
}					t_token;

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
	int				pipe_in;
	int				pipe_out;
	struct s_Parse	*next;
}					t_parse;

t_token	*ft_lstnewtoken(int type, char *value);
t_token	*ft_lstlasttoken(t_token *lst);
void	ft_lstaddtoken_back(t_token **lst, t_token *new);

t_Inout	*ft_lstnewinout(t_Inout *prev);
t_Inout	*ft_lstlastinout(t_Inout *lst);
void	ft_lstaddinout_back(t_Inout **lst, t_Inout *new);

t_parse	*ft_lstnewcmd(void);
t_parse	*ft_lstlastcmd(t_parse *lst);
void	ft_lstaddcmd_back(t_parse **lst, t_parse *new);

#endif
