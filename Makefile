# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/31 15:22:05 by hgeissle          #+#    #+#              #
#    Updated: 2023/04/03 11:19:54 by hgeissle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = srcs/main.c 

FLAGS = -Wall -Wextra -Werror -lreadline
INCLUDE = -I includes/minishell.h
AR = ar rcs
RM = rm -f
OBJS = $(SRC:.c=.o)

all: $(NAME)


$(NAME): $(OBJS)
	cc $(FLAGS) $(INCLUDE) $(OBJS) -o $(NAME)

%.o: %.c
	cc $(FLAGS) $(INCLUDE) -c $< -o $@

bonus: all

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re