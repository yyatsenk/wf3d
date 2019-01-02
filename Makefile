# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/10 10:13:16 by yyatsenk          #+#    #+#              #
#    Updated: 2018/12/10 10:13:17 by yyatsenk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = wolf3d

NOC=\033[0m
GRE=\033[32m
RED=\033[31m
YELL=\033[33m

cc = gcc
C_FLAGS = -Wall -Wextra -Werror 
FRAM = #-I minilibx -lmlx -framework OpenGL -framework AppKit -g

OBJ_PATH = ./obj/
LFT_PATH = ./libft/
INC_PATH = ./includes/

OBJ_NAME = $(SRC_NAME:.c=.o)
INC_NAME = wolf3d.h
SRC_NAME = main.c 
SRC = $(addprefix ,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
		@make -C $(LFT_PATH)
		@$(CC) -o $(NAME) $(FRAM) -L $(LFT_PATH) -lft $^ -o $@ 
		@echo "$(GRE)wolf3d DONE!$(GRE)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
		@mkdir -p $(OBJ_PATH) 2> /dev/null || true
		@$(CC) $(C_FLAGS) $(INC) -o $@ -c $<

clean:
		@make -C $(LFT_PATH) clean
		@rm -rf $(OBJ_PATH)
		@echo "$(RED)Removing OBJ path: ./obj$(RED)"

fclean: clean
		@make -C $(LFT_PATH) fclean
		@rm -f $(NAME)
		@echo "$(RED)Removing wolf3d executables$(RED)"

re: fclean all
