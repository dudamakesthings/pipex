# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: edribeir <edribeir@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2024/04/24 11:36:55 by edribeir      #+#    #+#                  #
#    Updated: 2024/04/24 18:54:31 by edribeir      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIBFT = ./Libft/libft.a

CFLAGS = -Wall -Werror -Wextra -g

RED = \033[31m
PINK = \033[35m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[96m
CYAN = \033[36m
RESET = \033[0m

SOURCE = TEST.c \

$(LIBFT):
	@$(MAKE) -C ./Libft

all: $(NAME)

OBJECTS = $(SOURCE:%.c=%.o)

%.o:%.c
	@cc $(CFLAGS) -c $^ -o $@

$(NAME): $(LIBFT) $(OBJECTS)
	@cc $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME)
	@echo "$(PINK)\t Ready!$(RESET)"

clean:
	@$(MAKE) clean -C ./Libft
	@rm -f $(OBJECTS)
	@echo "$(GREEN)\t OFILES Cleansed!$(RESET)"

fclean:
	@$(MAKE) fclean -C ./Libft
	@rm -f $(NAME)
	@rm -f $(OBJECTS)
	@echo "$(GREEN)\t ALL Cleansed!$(RESET)"

re: fclean all

PHONY: all clean fclean re