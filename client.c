/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti < ogorfti@student.1337.ma >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:33:30 by ogorfti           #+#    #+#             */
/*   Updated: 2023/01/26 15:27:18 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "ft_printf/ft_printf.h"

//SIGUSR2 = 0
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

void	ft_send_char(char c, pid_t pid)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (kill(pid, 0) == -1)
		{
			ft_printf("You're not writing the right PID!\n");
			exit (1);
		}
		if (c & (1 << i))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
		usleep(300);
	}
}

int	main(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac == 3)
	{
		if (!mini_atoi(av[1]))
		{
			ft_printf("You're not writing the right PID!\n");
			exit (1);
		}
		while (av[2][i])
		{
			ft_send_char(av[2][i], mini_atoi(av[1]));
			i++;
		}
	}
	else
		ft_printf("Alert format! ./client [server PID] [string must send it]\n");
	return (0);
}
