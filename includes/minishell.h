/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:30:33 by hgeissle          #+#    #+#             */
/*   Updated: 2023/04/23 20:46:43 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>
# include <fcntl.h>
# include "token.h"

# define ERROR 1
# define SUCCESS 0
# define PROMPT "minishell_alpha-0.1$ "

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	struct s_env	*env;
	size_t			env_size;
	char			*line;
	char			**command;
	char			*pwd;
	char			**envtab;
	int				exit_status;
}					t_data;

char				**env_list_to_tab(size_t env_size, t_env *envlst);
int					init_data(t_data *data, char **env);
int					check_command(char **command, t_data *data);
void				signal_handler(int signal);
int					set_env(t_data *data, const char *var, const char *new_val);
char				*get_env(t_env *env, const char *var);
int					print_env(t_env *env);
int					builtin_cd(t_data *data, char *str);
int					builtin_echo(char **command);
int					unset(t_env *env, char **names);
int					export(t_data *data, char **args);
int					ft_exit(t_data *data, char **args);
int					export_print(t_env *old_head);
t_env				*get_last(t_env *env);
void				ft_envadd_back(t_env **alst, t_env *new);
t_env				*ft_envnew(const char *name, const char *value);
int					del_elem(t_env *prev, t_env *to_del);
int					del_env(t_env *env, const char *var);
t_env				*find_env_node(t_env *env, const char *arg);
t_env				*get_previous(t_env *env, t_env *current);
void				ft_envclear(t_env **lst);
t_env				*ft_strarr_to_env(t_data *data, char **strarr);
char				*get_absolute_path(t_env *env, char *path, char *r_path);
long long			ft_atoi_long_long(const char *str);

/* ************************************************************************** */
/*                             Parsing                                        */
/* ************************************************************************** */

t_Token				create_tokens(t_list *elem, t_data *data);
t_Parse				*parse_command(t_Token *token);
void				parse_fd(t_Token *token, t_Parse *cmd);
void				exec_line(t_Parse *parse, t_data *data);
char				*get_binary_path(t_env *env, char *name);
void				here_doc(t_Inout *new);
char				*replace_env_variables(t_data *data, char *command);

#endif