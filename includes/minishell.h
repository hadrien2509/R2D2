/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:30:33 by hgeissle          #+#    #+#             */
/*   Updated: 2023/04/05 13:37:07 by sde-smed         ###   ########.fr       */
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

void	check_command(char **command, char *envp[]);
void	signal_handler(int signal);

#endif