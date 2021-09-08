# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/19 19:09:28 by azeraoul          #+#    #+#              #
#    Updated: 2021/09/08 14:22:47 by azeraoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:= gcc
NAME	:= fdf
CPPFLAGS	:= -I./libft/include -I./mlx
CFLAGS	:= -g -Wall -Wextra -Werror
LDFLAGS	:= -L./libft -L./mlx
LDLIBS	:= -lm -lft -lmlx -lX11 -lXext
FILES	:= fdf bresenham init parse utils
SRCS := $(addsuffix .c, $(addprefix srcs/, $(FILES)))
SRCS_B := $(addsuffix _bonus.c, $(addprefix srcs_bonus/, $(FILES)))
OBJS	:= $(SRCS:.c=.o)
OBJS_B	:= $(SRCS_B:.c=.o)
RM		:= rm -rf

ifeq ($(BONUS), 1)
	CPPFLAGS += -I./include_bonus
	SRCS = $(SRCS_B)
	OBJS = $(OBJS_B)
else
	CPPFLAGS += -I./include
endif

.PHONY:	all bonus clean re fclean

all: $(NAME)

bonus:
	make BONUS=1

$(NAME): $(OBJS)
	make --silent -C ./libft
	make --silent -C ./mlx
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	make clean --silent -C ./libft
	make clean --silent -C ./mlx
	$(RM) $(OBJS) $(OBJS_B)

fclean:	clean
	make fclean --silent -C ./libft
	$(RM) $(NAME)

re:	fclean all
