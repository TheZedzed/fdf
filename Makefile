# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/19 19:09:28 by azeraoul          #+#    #+#              #
#    Updated: 2021/08/19 22:04:04 by azeraoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:= gcc
NAME	:= fdf
CPPFLAGS	:= -I./libft/include -I./include -I./mlx
CFLAGS	:= -Wall -Wextra -Werror
LDFLAGS	:= -L./libft
LDLIBS	:= -lft -lmlx -lX11 -lXext
FILES	:= fdf coord_and_utils init max_min parse utils
FILES_B	:= fdf coord_and_utils init max_min parse utils adjust bresenham \
			keys
RM	:= rm -rf
SRCS := $(addsuffix .c, $(addprefix srcs/, $(FILES)))
SRCS_B := $(addsuffix _bonus.c, $(addprefix srcs_bonus/, $(FILES_B)))
OBJS := $(SRCS:.c=.o)
OBJS_B := $(SRCS_B:.c=.o)

ifeq ($(BONUS), 1)
	CPPFLAGS = -I./libft/include -I./include_bonus -I./mlx
	SRCS = $(SRCS_B)
endif

.PHONY:	all lft mlx bonus clean re fclean

all: $(NAME)

lft:
	make --silent -C ./libft

mlx:
	make --silent -C ./mlx

bonus:
	make BONUS=1

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME): lft $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

clean:
	make clean --silent -C ./libft
	$(RM) $(OBJS) $(OBJS_B)

fclean:	clean
	make fclean --silent -C ./libft
	$(RM) $(NAME)

re:	fclean all
