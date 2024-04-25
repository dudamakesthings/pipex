# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: edribeir <edribeir@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2024/04/24 11:36:55 by edribeir      #+#    #+#                  #
#    Updated: 2024/04/25 14:36:46 by edribeir      ########   odam.nl          #
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
BOLD = \033[1m
RESET = \033[0m

SOURCE = pipex.c \

OBJECTS = $(SOURCE:%.c=%.o)

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C ./Libft

$(NAME): $(LIBFT) $(OBJECTS)
	@cc $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME)
	@echo "$(PINK)$(BOLD)\n\t Ready! $(RESET)🎉\n"

%.o:%.c
	@cc $(CFLAGS) -c -o $@ $^ 

clean:
	@$(MAKE) clean -C ./Libft
	@rm -f $(OBJECTS)
	@echo "$(GREEN)\t OFILES Cleansed! $(RESET)🆗"

fclean:
	@$(MAKE) fclean -C ./Libft
	@rm -f $(NAME)
	@rm -f $(OBJECTS)
	@echo "$(GREEN)$(BOLD)\t ALL Cleansed! $(RESET)🆗"

re: fclean all

PHONY: all clean fclean re