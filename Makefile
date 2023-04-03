# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/31 15:22:05 by hgeissle          #+#    #+#              #
#    Updated: 2023/04/03 14:27:43 by sde-smed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = srcs/main.c 

READLINE_PATH = $(shell brew --prefix readline)
READLINE_LIB = -lreadline -lhistory -L $(READLINE_PATH)/lib
READLINE_INC = -I $(READLINE_PATH)/include 
LIBFT_LIB =  -L ./libft -lft
LIB = $(READLINE_LIB) $(LIBFT_LIB)
LIBFT	= libft/
FLAGS = -Wall -Wextra -Werror $(READLINE_LIB)
INCLUDE = -I includes/
AR = ar rcs
RM = rm -f
OBJS = $(SRC:.c=.o)

all: $(NAME)


$(NAME): $(OBJS)
	make -C $(LIBFT)
	cc $(FLAGS) $(INCLUDE) $(OBJS) -I $(LIBFT) $(LIB) -o $(NAME)

%.o: %.c
	cc $(CFLAGS) $(INCLUDE) -I $(READLINE_PATH)/include -c $< -o $@

bonus: all

clean:
		@make -C $(LIBFT) clean
		$(RM) $(OBJS)

fclean: clean
		@make -C $(LIBFT) fclean
		$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re