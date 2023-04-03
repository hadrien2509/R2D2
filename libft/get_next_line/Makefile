# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samy <samy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/30 11:43:52 by sde-smed          #+#    #+#              #
#    Updated: 2022/12/20 10:23:56 by samy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libgnl.a

SRC = 	get_next_line_bonus.c\
		get_next_line_utils_bonus.c
OBJ = $(SRC:.c=.o)

CC			=	cc

FLAG = -Wall -Wextra -Werror

ARRCS		=	ar rcs

RM		= rm -rf

.c.o:	$(SRCS)
	@$(CC) $(FLAGS) -c -o $@ $<

$(NAME): $(OBJ)
	@echo "make get_next_line"
	@$(ARRCS) $(NAME) $^
	
bonus: $(OBJ_BONUS) 
	$(ARRCS) $(NAME) $^
	
all: $(NAME)

clean:
	@$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY:			all clean fclean re bonus