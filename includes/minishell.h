/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:30:33 by hgeissle          #+#    #+#             */
/*   Updated: 2023/04/10 13:41:27 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>					// For readline
# include <readline/readline.h>		// For readline
# include <readline/history.h>		// For readline
# include <stdlib.h>				// For malloc
# include <signal.h>				// For signals
# include <unistd.h>				// For write
# include <termios.h>
# include "../libft/libft.h"

# define ERROR 1
# define SUCCESS 0
# define PROMPT "minishell_alpha-0.1$ "

typedef struct s_env {
	char				*var;
	struct s_env		*next;
}				t_env;


typedef struct s_data {
	struct s_env	*env;
	char			*line;
	char			**command;
}				t_data;

char    **ft_envlst_to_chararr(t_env *envlst);
int		get_env(t_env *env, char *var);
int		init_data(t_data *data, char **env);
void	check_command(char **command, t_data *data);
void	signal_handler(int signal);
int		set_env(t_env *env, char *var, char *new_val);

#endif