/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcili <bcili@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:00:47 by bcili             #+#    #+#             */
/*   Updated: 2025/03/22 13:00:47 by bcili            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

volatile sig_atomic_t	g_flag = 0;

void	check_flag(int sig)
{
	(void)sig;
	if (sig == SIGUSR1)
		g_flag = 1;
}

void	sig_sender(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if (c & (1 << bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (!g_flag)
			;
		g_flag = 0;
		bit++;
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*message;

	if (argc != 3)
	{
		ft_putstr("Error: wrong format.\n");
		ft_putstr("Try: ./client <PID> <message>\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (kill(pid, 0) == -1 || pid <= 0 || ft_strlen(argv[1]) > 7)
	{
		ft_putstr("Error: invalid PID.\n");
		return (1);
	}
	signal(SIGUSR1, check_flag);
	message = argv[2];
	while (*message)
		sig_sender(pid, *message++);
	sig_sender(pid, '\0');
	return (0);
}
