# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: edribeir <edribeir@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/10/20 13:36:22 by edribeir      #+#    #+#                  #
#    Updated: 2024/04/25 14:36:41 by edribeir      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

AR = ar -rsc

RED = \033[31m
PINK = \033[35m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[96m
CYAN = \033[36m
BOLD = \033[1m
RESET = \033[0m

SOURCE = ft_isdigit.c \
		ft_memset.c \
		ft_strlcpy.c \
		ft_substr.c \
		ft_atoi.c \
		ft_atol.c \
		ft_isprint.c \
		ft_split.c \
		ft_strlen.c	\
		ft_tolower.c \
		ft_bzero.c \
		ft_itoa.c \
		ft_strchr.c \
		ft_strmapi.c \
		ft_toupper.c \
		ft_calloc.c \
		ft_memchr.c \
		ft_strdup.c \
		ft_strncmp.c \
		ft_isalnum.c \
		ft_memcmp.c \
		ft_striteri.c \
		ft_strnstr.c \
		ft_isalpha.c \
		ft_memcpy.c \
		ft_strjoin.c \
		ft_strrchr.c \
		ft_isascii.c \
		ft_memmove.c \
		ft_strlcat.c \
		ft_strtrim.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putnbr_fd.c \
		ft_putendl_fd.c \
		ft_printf.c \
		ft_print_hex.c \
		ft_source.c \
		get_next_line.c \
		get_next_line_utils.c \
		# ft_lstnew.c \
		# ft_lstadd_front.c \
		# ft_lstsize.c \
		# ft_lstlast.c \
		# ft_lstadd_back.c \
		# ft_lstdelone.c \
		# ft_lstclear.c \
		# ft_lstiter.c \
		# ft_lstmap.c \

OBJECTS = $(SOURCE:%.c=%.o)

all: $(NAME)

$(NAME) : $(OBJECTS)
	@$(AR) $(NAME) $(OBJECTS)
	@echo "$(CYAN)$(BOLD)\t LIBFT DONE $(RESET)😊"

%.o:%.c 
	@$(CC) -c $(CFLAGS) -o $@ $^

clean: 
	@$(RM) $(OBJECTS)
	@echo "$(GREEN)\t LIBFT Cleansed! $(RESET)✅"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(GREEN)$(BOLD)\t LIBFT Library Cleansed! $(RESET)✅"

re: fclean all

.PHONY: all clean fclean re
