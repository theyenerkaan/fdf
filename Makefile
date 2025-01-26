# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 19:15:35 by yenyilma          #+#    #+#              #
#    Updated: 2025/01/26 15:27:04 by yenyilma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###############################################
#                  VARIABLES                  #
###############################################

NAME                =   fdf
HEADER              =   fdf.h
CC                  =   cc
CFLAGS              =   -Wall -Wextra -Werror -g
LIBFT               =   libft/libft.a
LIBFTDIR            =   libft
PRINTF              =   printf/libftprintf.a
PRINTFDIR           =   printf
GNL                 =   get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
GNLDIR              =   get_next_line
MLX                 =   mlx/libmlx.a
MLXDIR              =   mlx

SRC                 =   fdf_main.c fdf_alloc_free.c fdf_axis_locations.c \
                        fdf_draw_win.c fdf_error_check.c fdf_init_map.c \
                        fdf_key_utils.c fdf_loop_hook.c fdf_map_view.c \
                        fdf_parse_color.c fdf_parse_map.c fdf_set_menu.c \
                        fdf_utils.c ft_atoi_base.c ft_max.c ft_min.c \
                        $(GNL)

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

all: $(NAME)

$(NAME): $(LIBFT) $(PRINTF) $(GNL) $(MLX) $(OBJ) $(HEADER) 
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(PRINTF) $(MLX) -lm -lXext -lX11 -o $(NAME)
	@echo "$(COLOR_BOLD_GREEN)✔ Compilation complete!$(COLOR_RESET)"

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -I $(LIBFTDIR) -I $(PRINTFDIR) -I $(MLXDIR) -c $< -o $@

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

$(MLX): $(MLXDIR)
	@make -C mlx > /dev/null 2>&1

$(MLXDIR):
	@echo "$(COLOR_BOLD_CYAN)🌀 cloning mlx repository...$(COLOR_RESET)"
	@echo "$(COLOR_CYAN)"
	@git clone https://github.com/42Paris/minilibx-linux.git mlx
	@echo "$(COLOR_RESET)"

update:
	@echo "$(COLOR_BOLD_CYAN)🌀 updating all repositories...$(COLOR_RESET)"
	@echo "$(COLOR_BOLD_RED)"
	@cd libft && git pull
	@cd printf && git pull
	@cd get_next_line && git pull
	@cd mlx && git pull
	@echo "$(COLOR_RESET)"

bonus: all 

valgrind_fdf: $(NAME)
	@echo "$(COLOR_BOLD_CYAN)🔍 Running Valgrind for memory leaks...$(COLOR_RESET)"
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file=valgrind_fdf_out.txt ./$(NAME) $(ARGS)
	@echo "$(COLOR_BOLD_GREEN)✔ Valgrind check completed. See valgrind_fdf_out.txt$(COLOR_RESET)"

clean:
	@echo "$(COLOR_LIGHT_RED)🧹 Cleaning object files...$(COLOR_RESET)"
	@rm -rf $(OBJ)
	@make clean -C $(LIBFTDIR) > /dev/null 2>&1
	@make clean -C $(PRINTFDIR) > /dev/null 2>&1
	@make clean -C $(MLXDIR) > /dev/null 2>&1
	@echo "$(COLOR_LIGHT_RED)🧹 Object files cleaned.$(COLOR_RESET)"

fclean: clean
	@echo "$(COLOR_LIGHT_RED)🧹 removing object files and executables...$(COLOR_RESET)"
	@rm -rf $(NAME)
	@make fclean -C libft > /dev/null 2>&1
	@make fclean -C printf > /dev/null 2>&1
	@make clean -C mlx > /dev/null 2>&1
	@echo "$(COLOR_LIGHT_RED)🧹 all object files and executables removed.$(COLOR_RESET)"

re: fclean all
	@echo "$(COLOR_BOLD_GREEN)♻️  recompiled successfully... $(COLOR_RESET)" 