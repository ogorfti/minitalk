/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti < ogorfti@student.1337.ma >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:32:58 by ogorfti           #+#    #+#             */
/*   Updated: 2023/01/21 19:19:17 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "ft_printf/ft_printf.h"

void	signal_handler(int sig, siginfo_t *st, void *p)
{
	static char	c;
	static int	pid;
	static int	i;

	(void)p;
	if (st->si_pid != pid)
	{
		pid = st->si_pid;
		c = 0;
		i = 0;
	}
	c = c << 1;
	i++;
	if (sig == SIGUSR1)
		c = c | 1;
	if (i == 8)
	{
		write (1, &c, 1);
		i = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Process ID : %d\n", getpid());
	sa.sa_sigaction = &signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
