# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samy <samy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/31 15:22:05 by hgeissle          #+#    #+#              #
#    Updated: 2023/06/06 12:41:29 by samy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = main.c\
		close.c\
		signals.c\
		free.c\
		execute_fct.c\
		parsing.c\
		tokenizer.c\
		exec.c\
		token_struct.c\
		inout_struct.c\
		cmd_struct.c\
		check_command.c\
		commands.c\
		env_variables.c\
		cd_utils.c\
		echo.c\
		env.c\
		builtins.c\
		env_convertion.c\
		env_edition.c\
		export_utils.c\
		env_get.c\
		here_doc.c\
		split_command.c\
		ft_atoll.c\
		export.c\
		put_error.c\
		check_file.c\
		split_command_utils.c\
		tokenizer_utils.c\
		tokenizer_pipes.c\
		parse_fd.c\
		split_elem.c

SRCS_DIR = srcs
OBJS_DIR = objs
READLINE_PATH = $(shell brew --prefix readline)
READLINE_LIB = -lreadline -lhistory -L $(READLINE_PATH)/lib
READLINE_INC = -I $(READLINE_PATH)/include
LIBFT_LIB =  -L ./libft -lft
LIB = $(READLINE_LIB) $(LIBFT_LIB)
LIBFT	= libft/
FLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
INCLUDES = -I includes/ $(READLINE_INC) -I $(LIBFT)
AR = ar rcs
RM = rm -f
OBJS = $(addprefix ${OBJS_DIR}/, ${SRCS:%.c=%.o})
OBJ = $(SRCS:.c=.o)
        # Colors #
GREEN           =       \e[38;5;118m
YELLOW          =       \e[38;5;226m
RESET           =       \e[0m
_SUCCESS        =       [$(GREEN)SUCCESS$(RESET)]
_INFO           =       [$(YELLOW)INFO$(RESET)]

all: $(NAME)


$(NAME): $(OBJS)
	@make all -C $(LIBFT)
	@cc $(FLAGS) $(INCLUDES) $(OBJS) $(LIB) -o $(NAME)
	@printf "$(_SUCCESS) $(NAME) ready.\n"

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
	@mkdir -p ${@D}
	@cc $(FLAGS) $(INCLUDES) -c $< -o $@

bonus: all

clean:
		@make -C $(LIBFT) clean
		@${RM} -r ${OBJS_DIR}
		@printf "$(_INFO) $(NAME) objects folder removed.\n"

fclean:
		@make -C $(LIBFT) fclean
		@${RM} -r ${OBJS_DIR}
		@printf "$(_INFO) $(NAME) objects folder removed.\n"
		@${RM} ${NAME}
		@printf "$(_INFO) $(NAME) removed.\n"

re: fclean all

.PHONY: all clean fclean re