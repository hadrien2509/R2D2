/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 17:58:46 by hgeissle          #+#    #+#             */
/*   Updated: 2023/05/30 00:42:51 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum s_token_type
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
}					t_token_type;

typedef struct s_Token
{
	t_token_type	type;
	char			*value;
	int				arg_nb;
	struct s_Token	*prev;
	struct s_Token	*next;
}					t_token;

typedef struct s_in_out
{
	int				fd;
	char			*value;
	struct s_in_out	*prev;
	struct s_in_out	*next;
}					t_in_out;

typedef struct s_parse
{
	int				arg_nb;
	char			**cmd;
	t_in_out		*in;
	t_in_out		*out;
	int				pipe_in;
	int				pipe_out;
	struct s_parse	*next;
}					t_parse;

typedef struct s_pipe_data
{
	int				len;
	int				status;
	int				end[2];
	char			*str;
	char			*str_nonl;
}					t_pipe_data;

typedef struct s_parse_fd_data
{
	t_in_out		*new;
	t_in_out		*in;
	t_in_out		*out;
	t_parse			*cmd;
	t_token			*token;
	int				error;
}					t_parse_fd_data;

t_token				*ft_lstnewtoken(int type, char *value);
t_token				*ft_lstlasttoken(t_token *lst);
void				ft_lstaddtoken_back(t_token **lst, t_token *new);
t_in_out			*ft_lstnewinout(t_in_out *prev);
t_in_out			*ft_lstlastinout(t_in_out *lst);
void				ft_lstaddinout_back(t_in_out **lst, t_in_out *new);
t_parse				*ft_lstnewcmd(void);
t_parse				*ft_lstlastcmd(t_parse *lst);
void				ft_lstaddcmd_back(t_parse **lst, t_parse *new);

#endif
