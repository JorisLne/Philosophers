# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/24 13:28:29 by jlaine            #+#    #+#              #
#    Updated: 2024/10/28 15:55:26 by jlaine           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    =	philo
CC      =	cc
CFLAGS  =	-Wall -Wextra -Werror -pthread -g

HEADERS =	./includes/philo.h

SRCS    =	./sources/main.c ./sources/errors.c ./sources/parsing.c \
			./sources/init.c ./sources/free.c ./sources/reaper.c \
			./sources/routine.c ./sources/utils.c
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
BLINK	= \033[5m
BOLD	= \033[1m
