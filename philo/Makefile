# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/20 19:37:42 by akdovlet          #+#    #+#              #
#    Updated: 2024/05/20 19:55:04 by akdovlet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	philo

SRC		:=	main.c

SRC_DIR	:=	src

BUILD	:=	.build

SRC 	:=	$(addprefix $(SRC_DIR)/, $(SRC))

OBJ 	:=	$(patsubst $(SRC_DIR)/%.c, $(BUILD)/%.o, $(SRC))

DEPS 	:=	$(OBJ:.o=.d)

CC		:=	cc
CFLAGS	:=	-Wall -Werror -Wextra -MMD -MP -Iinclude

all: create_dirs $(NAME)

create_dirs: | $(BUILD)

$(BUILD):
	@if [ ! -d $(BUILD) ]; then mkdir $(BUILD); fi

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@printf "\033[1;32%sm\t$(CC) $(CFLAGS) $(OBJ) -o $(NAME)\033[0m\n";
	@printf "\033[1;32%sm\t$(NAME) ready\033[0m\n";

$(BUILD)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[1;32%sm\t$(CC) $(CFLAGS) -c $< -o $@\033[0m\n";
	@printf "\033[1;32%sm\tCompiled: $<\033[0m\n";

clean:
	@if [ -d $(BUILD) ]; then $(RM) -rf $(BUILD) && echo "\033[1;31m\tDeleted: $(NAME) $(BUILD)\033[0m"; fi

fclean: clean
	@if [ -f $(NAME) ]; then $(RM) -rf $(NAME) && echo "\033[1;31m\tDeleted: $(NAME)\033[0m"; fi

re: fclean all

-include $(DEPS)

.PHONY: all create_dirs clean fclean re
