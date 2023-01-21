/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti < ogorfti@student.1337.ma >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:33:30 by ogorfti           #+#    #+#             */
/*   Updated: 2023/01/21 15:24:12 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

//SIGUSR2 = 0
void	ft_send_char(char c, pid_t pid)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (c & (1 << i))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
		usleep(250);
	}
}

int	main(int ac, char **av)
{
	int		i;
	pid_t	pid;

	i = 0;
	pid = atoi(av[1]);
	if (ac == 3)
	{
		while (av[2][i])
		{
			ft_send_char(av[2][i], pid);
			i++;
		}
	}
	else
		write(1, "ERROR\n", 7);
	return (0);
}
