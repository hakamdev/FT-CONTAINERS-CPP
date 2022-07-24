# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/06 23:17:59 by ehakam            #+#    #+#              #
#    Updated: 2022/07/24 02:49:14 by ehakam           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*- Makefile -*-

SRC	= tests/mamoussa_main.cpp
NAME= test.out
FLGS= -Wall -Wextra -Werror --std=c++98 #-fsanitize=address

all: $(NAME)

$(NAME): $(SRC)
	@c++ $(FLGS) $(SRC) -o $(NAME)

clean:
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
