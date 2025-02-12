# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: drafe <drafe@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/12 20:00:16 by drafe             #+#    #+#              #
#    Updated: 2019/10/16 12:22:42 by drafe            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

NAME = fractol

HEADERS = fractol.h\
	keys.h

LIBS = -L./Libft/ -lft\
	-lmlx -framework OpenGL -framework AppKit

OBJS = main.o\
	ft_new_win.o\
	ft_draw.o\
	ft_ui.o\
	ft_ui_exp.o\
	ft_colors.o\
	ft_mand.o\
	ft_julia.o\
	ft_mand_fish.o\
	ft_mand_tricorn.o\
	ft_self_call.o\
	ft_carpet.o\
	ft_henon.o\
	ft_sierpinski.o\
	ft_burning_ship.o\
	ft_rand_walk.o

all: $(NAME)

$(NAME):$(OBJS) | lib
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) -l pthread

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ -c $<

lib:
	@make -f Makefile.libft

clean:
	@make -f Makefile.libft clean
	@rm -rf $(OBJS)

fclean: clean
	@make -f Makefile.libft fclean
	@rm -f $(NAME)

re: fclean all
 