# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ogorfti < ogorfti@student.1337.ma >        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 16:33:33 by ogorfti           #+#    #+#              #
#    Updated: 2023/01/19 19:16:26 by ogorfti          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all : client server

client : client.o
	$(CC) $(CFLAGS) client.o -o client

server : server.o
	$(CC) $(CFLAGS) server.o -o server

client_bonus : client_bonus.o
	$(CC) $(CFLAGS) client_bonus.o -o client

server_bonus : server_bonus.o
	$(CC) $(CFLAGS) server_bonus.o -o server

bonus : client_bonus server_bonus

clean :
		$(RM) server.o client.o client_bonus.o server_bonus.o

fclean : clean
		$(RM) server client

re : fclean all

me : all clean

be : bonus clean