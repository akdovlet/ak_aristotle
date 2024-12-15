# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/20 19:37:42 by akdovlet          #+#    #+#              #
#    Updated: 2024/12/15 15:27:11 by akdovlet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	philo

SRC		:=	atol.c			\
			clear.c			\
			link_data.c		\
			main.c			\
			monitor.c		\
			routine_sequence.c	\
			routine_state.c	\
			routine.c		\
			setup_threads.c	\
			setup.c			\
			time.c
SRC_DIR	:=	src
BUILD	:=	.build
SRC 	:=	$(addprefix $(SRC_DIR)/, $(SRC))
OBJ 	:=	$(patsubst $(SRC_DIR)/%.c, $(BUILD)/%.o, $(SRC))
DEPS 	:=	$(OBJ:.o=.d)

CC		:=	cc
CFLAGS	:=	-Wall -Werror -Wextra -MMD -MP -Iinclude -g -pthread

all: create_dirs $(NAME)

create_dirs: | $(BUILD)

$(BUILD):
	@if [ ! -d $(BUILD) ]; then mkdir -p $(BUILD); fi

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@printf "\033[1;32%sm\t$(NAME) ready\033[0m\n";

$(BUILD)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[1;32%sm\tCompiled: $<\033[0m\n";

clean:
	@if [ -d $(BUILD) ]; then $(RM) -rf $(BUILD) && printf "\033[1;31m\tDeleted: $(NAME) $(BUILD)\033[0m\n"; fi

fclean: clean
	@if [ -f $(NAME) ]; then $(RM) -rf $(NAME) && printf "\033[1;31m\tDeleted: $(NAME)\033[0m\n"; fi

val: all
	valgrind --leak-check=full --track-fds=yes --trace-children=yes --tool=helgrind ./${NAME}

full: all
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes --tool=helgrind ./${NAME}

re:
	@make --no-print-directory fclean
	@make --no-print-directory all

-include $(DEPS)

.PHONY: all create_dirs clean fclean re
