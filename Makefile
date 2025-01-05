# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 19:15:35 by yenyilma          #+#    #+#              #
#    Updated: 2025/01/05 19:16:04 by yenyilma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###############################################
#                  VARIABLES                  #
###############################################

NAME                =   fdf
HEADER              =   fdf.h
B_HEADER            =   fdf.h
CC                  =   cc
CFLAGS              =   -Wall -Werror -Wextra -g
LIBFT               =   libft/libft.a
LIBFTDIR            =   libft
PRINTF              =   printf/libftprintf.a
PRINTFDIR           =   printf
GNL                 =   get_next_line/get_next_line
GNLDIR              =   get_next_line

SRC                 =   push_swap.c data_parser.c ft_lstsort.c ft_stackclear.c ft_stacknew.c \
						ft_stackpop.c ft_stackpush.c help.c operation.c push_operations.c \
						r_rotate_operations.c rotate_operations.c stack_help.c \
						swap_operations.c target.c transaction.c ft_atol.c

B_SRC               =   checker_bonus.c data_parser_bonus.c ft_lstsort_bonus.c ft_stackclear_bonus.c \
						ft_stacknew_bonus.c ft_stackpop_bonus.c ft_stackpush_bonus.c help_bonus.c \
						operation_bonus.c push_operations_bonus.c r_rotate_operations_bonus.c \
						rotate_operations_bonus.c stack_help_bonus.c swap_operations_bonus.c \
						target_bonus.c transaction_bonus.c ft_atol_bonus.c

OBJ                 =   $(SRC:.c=.o)
B_OBJ               =   $(B_SRC:.c=.o)

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

all: $(NAME)

$(NAME): $(LIBFT) $(PRINTF) $(OBJ) $(HEADER)
	@$(CC) $(OBJ) $(LIBFT) $(PRINTF) -o $(NAME)
	@echo "$(COLOR_LIGHT_PURPLE)✔ push_swap successfully compiled...$(COLOR_RESET)"

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -I $(LIBFTDIR) -I $(PRINTFDIR) -c $< -o $@
	@echo "$(COLOR_LIGHT_GREEN)compiling $<...$(COLOR_RESET)"

$(LIBFT): $(LIBFTDIR)
	@make bonus -C libft > /dev/null 2>&1

$(LIBFTDIR):
	@echo "$(COLOR_BOLD_CYAN)🌀 cloning libft repository...$(COLOR_RESET)"
	@echo "$(COLOR_CYAN)"
	@git clone git@github.com:theyenerkaan/libft.git libft
	@echo "$(COLOR_RESET)"

$(PRINTF): $(PRINTFDIR)
	@make -C printf > /dev/null 2>&1

$(PRINTFDIR):
	@echo "$(COLOR_BOLD_CYAN)🌀 cloning printf repository...$(COLOR_RESET)"
	@echo "$(COLOR_CYAN)"
	@git clone git@github.com:theyenerkaan/printf.git printf
	@echo "$(COLOR_RESET)"

$(GNL): $(GNLDIR)
	@make -C get_next_line > /dev/null 2>&1

$(GNLDIR):
	@echo "$(COLOR_BOLD_CYAN)🌀 cloning get_next_line repository...$(COLOR_RESET)"
	@echo "$(COLOR_CYAN)"
	@git clone git@github.com:theyenerkaan/get_next_line_true.git get_next_line
	@echo "$(COLOR_RESET)"

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