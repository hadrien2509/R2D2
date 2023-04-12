/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:30:33 by hgeissle          #+#    #+#             */
/*   Updated: 2023/04/12 20:15:16 by samy             ###   ########.fr       */
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

# define ERROR 1
# define SUCCESS 0
# define PROMPT "minishell_alpha-0.1$ "

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	struct s_env	*env;
	unsigned int	env_size;
	char			*line;
	char			**command;
}					t_data;

char				**env_list_to_tab(unsigned int env_size, t_env *envlst);
int					init_data(t_data *data, char **env);
int					check_command(char **command, t_data *data);
void				signal_handler(int signal);
int					set_env(t_env *env, char *var, char *new_val);
char				*get_env(t_env *env, char *var);
int					builtin_cd(t_env *env, char *str);
int					print_env(t_env *env);
int					builtin_echo(char **command);
t_env				*get_last(t_env *env);
void				ft_envadd_back(t_env **alst, t_env *new);
t_env				*ft_envnew(char *var);
int					export(t_env *env, char *arg);
int					unset(t_env *env, char *arg);
int					del_elem(t_env *prev, t_env *to_del);
int					del_env(t_env *env, char *var);
t_env				*get_env_t(t_env *env, char *arg);
t_env				*get_previous(t_env *env, t_env *current);
#endif