# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ogorfti < ogorfti@student.1337.ma >        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 16:33:33 by ogorfti           #+#    #+#              #
#    Updated: 2023/01/26 15:25:48 by ogorfti          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#If you use the same variable names for different targets in your makefile, it
#will overwrite the previous definition of that variable and the previous build
#will not be taken into consideration when the new target is built. This may 
#cause the previous build to be relinked again, even if it has not been modified.
#To avoid this, you can use different variable names for different 
#targets, or you can use pattern rules to make the build process more efficient.

NAME = client

NAME1 = server

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

LIBR = ft_printf/libftprintf.a

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME) $(NAME1)

$(NAME) : client.o
	make -C ft_printf
	$(CC) $(CFLAGS) client.o ft_printf/libftprintf.a -o $(NAME)

$(NAME1) : server.o
	make -C ft_printf
	$(CC) $(CFLAGS) server.o ft_printf/libftprintf.a -o $(NAME1)

bonus : client_bonus server_bonus

client_bonus : client_bonus.o
	make -C ft_printf
	$(CC) $(CFLAGS) client_bonus.o ft_printf/libftprintf.a -o client_bonus

server_bonus : server_bonus.o
	make -C ft_printf
	$(CC) $(CFLAGS) server_bonus.o ft_printf/libftprintf.a -o server_bonus

clean :
		make clean -C ft_printf
		$(RM) server.o client.o client_bonus.o server_bonus.o

fclean : clean
		$(RM) server client client_bonus server_bonus
		make fclean -C ft_printf

re : fclean all
