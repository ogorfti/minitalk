/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti < ogorfti@student.1337.ma >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:05:23 by ogorfti           #+#    #+#             */
/*   Updated: 2023/01/21 16:55:02 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

static pid_t	g_oldpid;

void	reset_variables(int *i, int *k, int *count, char *c)
{
	int	j;

	j = 0;
	*i = 0;
	*k = 0;
	*count = 0;
	while (j < 4)
	{
		c[j] = 0;
		j++;
	}
}

void	check_end(char c)
{
	if (c == 0)
		kill (g_oldpid, SIGUSR1);
}

void	write_output(int *i, int *k, int *count, char *c)
{
	if ((*i == 8 && *k == 0) || (*i == 16 && *k == 2)
		|| (*i == 24 && *k == 3) || (*i == 32 && *k == 4))
	{
		if (*k == 0)
		{
			write(1, c, 1);
			check_end(c[0]);
		}
		else
			write(1, c, *k);
		reset_variables(i, k, count, c);
	}
	else if (!(*i == 32 && *k == 4))
		*count = *count + 1;
}

void	signal_handler(int sig, siginfo_t *st, void *p)
{
	static char		c[4];
	static int		i;
	static int		count;
	static int		k;

	(void)p;
	if (g_oldpid != st->si_pid)
	{
		g_oldpid = st->si_pid;
		reset_variables(&i, &k, &count, c);
	}
	c[count] = c[count] << 1;
	if (sig == SIGUSR1)
	{
		if (i < 4 && k == i)
			k++;
		c[count] = c[count] | 1;
	}
	i++;
	if (i == 8 || i == 16 || i == 24 || i == 32)
		write_output(&i, &k, &count, c);
}

int	main(void)
{
	struct sigaction	sa;

	printf("Process ID : %d\n", getpid());
	sa.sa_sigaction = &signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
