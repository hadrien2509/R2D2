/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:30:33 by hgeissle          #+#    #+#             */
/*   Updated: 2023/04/03 13:31:42 by hgeissle         ###   ########.fr       */
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

# define ERROR 1
# define SUCCESS 0

#endif