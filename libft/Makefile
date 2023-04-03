# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/04 11:24:14 by samy              #+#    #+#              #
#    Updated: 2023/04/03 14:24:05 by sde-smed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

PRINTF = 	printf/ft_printf.c\
		printf/ft_printf_utils.c\
		printf/ft_printf_utils_print.c

GNL = 	get_next_line/get_next_line.c\
		get_next_line/get_next_line_utils.c
SRC = 	ft_atoi.c\
		ft_isalpha.c\
		ft_isdigit.c\
		ft_isalnum.c\
		ft_isascii.c\
		ft_isprint.c\
		ft_strlen.c\
		ft_memset.c\
		ft_bzero.c\
		ft_memcpy.c\
		ft_strlcpy.c\
		ft_memmove.c\
		ft_strlcat.c\
		ft_toupper.c\
		ft_tolower.c\
		ft_strchr.c\
		ft_strrchr.c\
		ft_strncmp.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_strnstr.c\
		ft_calloc.c\
		ft_strdup.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_strtrim.c\
		ft_split.c\
		ft_itoa.c\
		ft_strmapi.c\
		ft_striteri.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_strrncmp.c
		
SRCS = $(SRC) $(PRINTF) $(GNL)
OBJ = $(SRCS:.c=.o)

BONUS = ft_lstnew.c\
		ft_lstadd_front.c\
		ft_lstsize.c\
		ft_lstlast.c\
		ft_lstadd_back.c\
		ft_lstdelone.c\
		ft_lstclear.c\
		ft_lstiter.c\
		ft_lstmap.c

OBJ_BONUS = $(BONUS:.c=.o)

CC			=	cc

FLAG = -Wall -Wextra -Werror

ARRCS		=	ar rcs

RM		= rm -rf

.c.o:	$(SRCS)
	@$(CC) $(FLAGS) -c -o $@ $<

$(NAME): $(OBJ)
	@echo "make libft"
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