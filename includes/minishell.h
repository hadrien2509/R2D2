/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:30:33 by hgeissle          #+#    #+#             */
/*   Updated: 2023/06/09 13:08:01 by sde-smed         ###   ########.fr       */
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
# include <sys/stat.h>
# include "token.h"

# define ERROR 1
# define SUCCESS 0
# define PROMPT "minihell🔥 "

int	g_exit_status;

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
	int				old_exit_status;
	t_split_elem	*split;
}					t_data;

typedef struct s_handle
{
	t_data			*data;
	t_split_elem	*first;
	char			*command;
}					t_handle;

char				**env_list_to_tab(size_t env_size, t_env *envlst);
int					init_data(t_data *data, char **env);
void				signal_handler(int signal);
void				signal_handler_child(int signal);
int					set_env(t_data *data, const char *var, const char *new_val);
char				*get_env(t_env *env, const char *var);
int					print_env(int fd, t_env *env, char **args);
int					builtin_cd(t_data *data, char *str);
int					builtin_echo(int fd, char **command);
int					unset(t_env *env, char **names);
int					export(int fd, t_data *data, char **args);
int					ft_exit_builtin(t_data *data, char **args);
int					export_print(int fd, t_env *old_head);
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
long long int		*ft_atoll(const char *str, long long int *result);
int					print_error(char *builtin, char *str, char *cmd, int value);
int					is_directory(char *cmd);
int					can_execute(char *file);
int					is_file(char *cmd);
int					can_read(char *file);
int					can_write(char *file);
char				*handle_spaces(char *ptr, t_handle *handle);
char				*handle_special_chars(char *ptr, t_handle *handle);
int					add_command_to_list(t_handle *handle, char *str,
						int is_special);
void				init_handle(t_handle *handle, t_data *data, char *command);
int					create_tokens(t_data *data, t_token **token);
t_parse				*parse_command(t_token *token);
int					parse_fd(t_token *token, t_parse *cmd, t_data *data);
void				exec_line(t_parse *parse, t_parse *start, t_data *data);
char				*get_binary_path(t_env *env, char *name);
int					create_heredoc(t_data *data, t_in_out **new, t_in_out **in,
						t_token *token);
char				*replace_env_variables(t_data *data, char *command);
char				*get_cmd_path(char *arg, t_data *data);
int					check_builtins(char *arg);
int					redirec(t_parse *parse);
char				*replace_env_variables(t_data *data, char *command);
t_split_elem		*split_command(t_data *data, char *command);
void				syntax_error(int error, char *str);
int					redirec_tokenizer(t_split_elem **elem, t_token **new);
void				free_parse(t_parse *parse);
void				free_tokens(t_token *token);
int					cmd_pipes_tokenizer(t_split_elem *elem, t_token **new,
						t_data *data, int *arg_need);
int					complete_pipe(t_data *data, t_split_elem *elem);
int					parse_fd_token(t_token *token, t_parse_fd_data *fd_data,
						t_data *data);
t_parse_fd_data		*init_parse_fd_data(t_parse_fd_data *fd_data, t_parse *cmd,
						t_token *token);
int					create_file(t_in_out **new, t_in_out **inout,
						t_token *token);
void				set_pipes(t_parse *cmd);
int					execute(t_parse *parse, t_data *data, int pid);
void				quit(t_data *data, int status);
int					exec_exit_handler(int pid, t_parse *parse);
void				close_fd(t_parse *parse);
int					add_command(t_handle *handle, char *str, int is_special);
char				*add_empty(t_handle *handle, char *ptr);
int					builtins(t_data *data, t_parse *parse, int fd);
void				check_signal(t_data *data, int result);
#endif