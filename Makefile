# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/31 15:22:05 by hgeissle          #+#    #+#              #
#    Updated: 2023/04/03 11:46:44 by hgeissle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = srcs/main.c 

READLINE_PATH = $(shell brew --prefix readline)
READLINE_LIB = -lreadline -lhistory -L $(READLINE_PATH)/lib
READLINE_INC = -I $(READLINE_PATH)/include 

FLAGS = -Wall -Wextra -Werror
INCLUDE = -I includes/
AR = ar rcs
RM = rm -f
OBJS = $(SRC:.c=.o)

all: $(NAME)


$(NAME): $(OBJS)
	cc $(FLAGS) $(INCLUDE) $(READLINE_LIB) $(OBJS) -o $(NAME)

%.o: %.c
	cc $(CFLAGS) $(INCLUDE) -I $(READLINE_PATH)/include -c $< -o $@

bonus: all

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re