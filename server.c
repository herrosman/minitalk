/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosman <aosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:13:41 by aosman            #+#    #+#             */
/*   Updated: 2025/08/03 20:47:55 by aosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_server g_data = {0, 0, 0};

/**
 * @brief Signal handler for server. Processes each bit received from clients.
 *
 * @param sig Signal type (SIGUSR1 for 0, SIGUSR2 for 1)
 * @param info Signal information (contains sender PID)
 * @param context Unused context parameter
 */
static void server_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;

	// Handle new client or interrupt from different client
	if (g_data.bit_count == 0 && g_data.client_pid == 0)
		g_data.client_pid = info->si_pid;
	else if (g_data.client_pid != info->si_pid) {
		g_data.current_char = 0;
		g_data.bit_count = 0;
		g_data.client_pid = info->si_pid;
	}

	// Process bit: SIGUSR1=0, SIGUSR2=1
	g_data.current_char |= ((sig == SIGUSR2) << g_data.bit_count);
	g_data.bit_count++;

	// Complete byte received
	if (g_data.bit_count == 8) {
		if (g_data.current_char == '\0') {
			// End of message: reset state
			g_data.current_char = 0;
			g_data.bit_count = 0;
			g_data.client_pid = 0;
		} else {
			// Print character and reset byte buffer
			write(STDOUT_FILENO, &g_data.current_char, 1);
			g_data.current_char = 0;
			g_data.bit_count = 0;
		}
	}

	// Acknowledge bit receipt
	kill(info->si_pid, SIGUSR1);
}

int main(void)
{
	struct sigaction sa;

	// Print server PID for client connection
	ft_printf("Server PID: %d\n", getpid());

	// Configure signal handling
	sa.sa_sigaction = server_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);

	if (sigaction(SIGUSR1, &sa, NULL) < 0 ||
		sigaction(SIGUSR2, &sa, NULL) < 0) {
		ft_putstr_fd("Error setting signal handlers\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}

	// Main loop: wait for signals indefinitely
	while (1)
		pause();

	return (0);
}
