# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/23 13:33:39 by jlaine            #+#    #+#              #
#    Updated: 2024/10/24 15:43:32 by jlaine           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    =	philo_bonus
CC      =	cc
CFLAGS  =	-Wall -Wextra -Werror -pthread -g

HEADERS =	./includes/philo_bonus.h

SRCS    =	./sources/init.c ./sources/main.c ./sources/free.c \
			./sources/parsing.c ./sources/routine.c ./sources/utils.c
OBJS    =	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)$(BOLD)> Ongoing..$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo "$(GREEN)$(BLINK)$(BOLD)Program $(NAME) created!$(RESET)"

$(OBJS): %.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "$(CYAN)$(BLINK)$(BOLD)Objects files removed.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(CYAN)$(BLINK)$(BOLD)Executable removed.$(RESET)"

re: fclean all

.PHONY: all clean fclean re

# COLORS
GREEN	= \033[32m
BLUE	= \033[34m
YELLOW	= \033[1;33m
CYAN	= \033[36m
BLINK	= \033[5m
BOLD	= \033[1m
ERASE	= \033[2K\r
RESET	= \033[0m
BOLD	= \033[1m