# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 17:30:42 by yenyilma          #+#    #+#              #
#    Updated: 2024/12/12 17:52:12 by yenyilma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line
HEADER = get_next_line.h
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rc
SRC = get_next_line.c get_next_line_utils.c

OBJ = $(SRC:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	@$(AR)  $(NAME) $(OBJ)
	@echo "compiling..."

%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJ)

fclean :
	@rm -rf  $(NAME) $(OBJ)

re : fclean all

