/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti < ogorfti@student.1337.ma >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:05:11 by ogorfti           #+#    #+#             */
/*   Updated: 2023/01/21 21:30:43 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "ft_printf/ft_printf.h"

int	mini_atoi(char *str)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
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
		ft_printf("All strings have been received\n");
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
	pid = mini_atoi(av[1]);
	if (pid <= 1)
		exit(1);
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
