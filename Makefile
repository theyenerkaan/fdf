# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 19:15:35 by yenyilma          #+#    #+#              #
#    Updated: 2025/01/16 19:08:25 by yenyilma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###############################################
#                  VARIABLES                  #
###############################################

NAME                =   fdf
HEADER              =   fdf.h
CC                  =   cc
CFLAGS              =   -Wall -Werror -Wextra -g
LIBFT               =   libft/libft.a
LIBFTDIR            =   libft
PRINTF              =   printf/libftprintf.a
PRINTFDIR           =   printf
GNL                 =   get_next_line/get_next_line.a
GNLDIR              =   get_next_line

SRC                 =   fdf.c fdf_error_msg.c fdf_map.c fdf_set.c fdf_utils.c fdf_set_color.c

OBJ                 =   $(SRC:.c=.o)
###############################################
#                 COLORS                       #
###############################################

COLOR_RED           =   \033[0;31m
COLOR_BOLD_RED      =   \033[1;31m
COLOR_LIGHT_RED     =   \033[0;91m
COLOR_GREEN         =   \033[0;32m
COLOR_BOLD_GREEN    =   \033[1;32m
COLOR_LIGHT_GREEN   =   \033[0;92m
COLOR_BLUE          =   \033[0;34m
COLOR_BOLD_BLUE     =   \033[1;34m
COLOR_LIGHT_BLUE    =   \033[0;94m
COLOR_PURPLE        =   \033[0;35m
COLOR_BOLD_PURPLE   =   \033[1;35m
COLOR_LIGHT_PURPLE  =   \033[0;95m
COLOR_CYAN          =   \033[0;36m
COLOR_BOLD_CYAN     =   \033[1;36m
COLOR_LIGHT_CYAN    =   \033[0;96m
COLOR_RESET         =   \033[0m

###############################################
#                  TARGETS                    #
###############################################

all: 
	cc fdf.c fdf_error_msg.c fdf_keycode.c fdf_locations.c fdf_map.c fdf_set.c fdf_set_color.c fdf_utils.c ft_max.c ft_min.c libft/libft.a printf/libftprintf.a get_next_line/get_next_line.c get_next_line/get_next_line_utils.c mlx/libmlx.a -lXext -lX11 -lm -o fdf

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -I $(LIBFTDIR) -I $(PRINTFDIR) -I $(GNLDIR) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(PRINTF):
	$(MAKE) -C $(PRINTFDIR)

$(GNL):
	$(MAKE) -C $(GNLDIR)

update:
	@echo "$(COLOR_BOLD_CYAN)🌀 updating all repositories...$(COLOR_RESET)"
	@echo "$(COLOR_BOLD_RED)"
	@cd libft && git pull
	@cd printf && git pull
	@cd get_next_line && git pull
	@echo "$(COLOR_RESET)"

bonus: all $(CHECKER)

$(CHECKER): $(LIBFT) $(PRINTF) $(GNL) $(B_OBJ) $(B_HEADER)
	@$(CC) $(B_OBJ) $(LIBFT) $(PRINTF) $(GNL) -o $(CHECKER)
	@echo "$(COLOR_BOLD_PURPLE)✔ checker successfully compiled...$(COLOR_RESET)"

valgrind_push_swap: $(NAME)
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file=valgrind_push_swap_out.txt ./$(NAME) $(ARGS)

clean:
	@echo "$(COLOR_LIGHT_RED)🧹 cleaning object files...$(COLOR_RESET)"
	@rm -rf $(OBJ) $(B_OBJ)
	@make clean -C libft > /dev/null 2>&1
	@make clean -C printf > /dev/null 2>&1
	@echo "$(COLOR_LIGHT_RED)🧹 object files cleaned.$(COLOR_RESET)"

fclean: clean
	@echo "$(COLOR_LIGHT_RED)🧹 removing object files and executables...$(COLOR_RESET)"
	@rm -rf $(NAME) $(CHECKER)
	@make fclean -C libft > /dev/null 2>&1
	@make fclean -C printf > /dev/null 2>&1
	@make fclean -C get_next_line > /dev/null 2>&1
	@echo "$(COLOR_LIGHT_RED)🧹 all object files and executables removed.$(COLOR_RESET)"

re: fclean all
	@echo "$(COLOR_BOLD_GREEN)♻️  recompiled successfully... $(COLOR_RESET)"