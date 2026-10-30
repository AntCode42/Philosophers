# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agard <agard@student.42lausanne.ch>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/23 10:24:04 by agard             #+#    #+#              #
#    Updated: 2026/02/23 11:03:05 by agard            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ====== CONFIG ======

NAME		= philo

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
RM			= rm -f

SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= include

SRC			= $(shell find $(SRC_DIR) -name "*.c")
OBJ			= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

INCLUDES	= -I $(INC_DIR)

.DEFAULT_GOAL := all

# ====== RULES ======

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "\033[0;32m$(NAME) compiled successfully ✔\033[0m"

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re