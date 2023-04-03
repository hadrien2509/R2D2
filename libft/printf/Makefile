# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samy <samy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/04 11:24:14 by samy              #+#    #+#              #
#    Updated: 2022/12/20 10:24:01 by samy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libprintf.a

SRCS = 	ft_printf.c\
		ft_printf_utils.c\
		ft_printf_utils_print.c
		
OBJS = $(SRCS:.c=.o)

CC			=	cc

FLAG = -Wall -Wextra -Werror

ARRCS		=	ar rcs

RM		= rm -rf

.c.o:	$(SRCS)
	@$(CC) $(FLAGS) -c -o $@ $<

$(NAME): $(OBJS)

	@echo "make printf"
	@$(ARRCS) $(NAME) $^
	
all: $(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY:			all clean fclean re
