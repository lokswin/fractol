# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: drafe <drafe@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/12 20:00:16 by drafe             #+#    #+#              #
#    Updated: 2019/09/06 20:49:51 by drafe            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

NAME = fractol

HEADERS = fractol.h

LIBS = -L./Libft/ -lft\
	-lmlx -framework OpenGL -framework AppKit

OBJS = main.o\
	

all: $(NAME)

$(NAME):$(OBJS) | lib
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -o $@ -c $<

lib:
	@make -f Makefile.libft

clean:
	@make -f Makefile.libft clean
	@rm -rf $(OBJS)

fclean: clean
	@make -f Makefile.libft fclean
	@rm -f $(NAME)

re: fclean all

