/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti < ogorfti@student.1337.ma >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:05:11 by ogorfti           #+#    #+#             */
/*   Updated: 2023/01/21 15:40:08 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

int mini_atoi(char *str)
{
	int	i;
	int r;
	
	i = 0;
	r = 0;
	while(str[i])
	{
		r = r * 10;
		r = r + str[i] - '0';
		i++;
	}
	return (r);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	handle_message(int sig)
{
	if (sig == SIGUSR1)
		write(1, "All strings have been received\n", 32);
}

void	ft_shift(char c, pid_t pid)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((c & (1 << i)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
		usleep (250);
	}
}

int	main(int ac, char **av)
{
	pid_t	pid;
	int		i;

	i = 0;
	pid = atoi(av[1]);
	signal (SIGUSR1, handle_message);
	if (ac == 3)
	{
		while (i <= ft_strlen(av[2]))
		{
			ft_shift(av[2][i], pid);
			i++;
		}
	}
	return (0);
}
