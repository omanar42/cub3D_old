# *********************************************** #
#      ____  ____ ___  ____ _____  ____ ______    #
#     / __ \/ __ `__ \/ __ `/ __ \/ __ `/ ___/    #
#    / /_/ / / / / / / /_/ / / / / /_/ / /        #
#    \____/_/ /_/ /_/\__,_/_/ /_/\__,_/_/         #
#                                                 #
#    Makefile                                     #
#    By: omanar <omanar@student.1337.ma>          #
#    Created: 2022/08/15 07:08 PM by omanar 	  #
#                                                 #
# *********************************************** #

NAME	=	cub3D
RM		=	rm -f
CC		=	gcc -Wall -Wextra -Werror -Iincludes -I libs/libft/includes #-g -fsanitize=address
MLXFLG	=	-lmlx -framework OpenGL -framework AppKit
LIBFT	=	libs/libft/libft.a
SRCS	=	srcs/cub3D.c srcs/parsing/parsing.c srcs/utils/error_handler.c $(LIBFT)

define HEADER_M
   ______      __   _____ ____ 
  / ____/_  __/ /_ |__  // __ \\
 / /   / / / / __ \\ /_ </ / / /
/ /___/ /_/ / /_/ /__/ / /_/ / 
\\____/\\__,_/_.___/____/_____/  
endef
export HEADER_M

all: header_m $(NAME)

header_m:
	@echo "\033[0;33m$$HEADER_M\033[0m\n"

$(LIBFT):
	@echo "\033[0;36m</ Compiling libft >\033[0m"
	@make -C libs/libft

$(NAME): $(SRCS) $(LIBFT)
	@echo "\033[0;36m</ Compiling Cub3D >\033[0m"
	@$(CC) $(MLXFLG) $(SRCS) -o $(NAME)
	@echo "\033[1;32mCub3D has been compiled!\033[0m\n"

clean:
	@make clean -C libs/libft

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libs/libft
	@echo "\n\033[0;31m</ EVERYTHING HAS BEEN DELETED! >\033[0m\n"

re: fclean all

.PHONY: all clean fclean re header_m
