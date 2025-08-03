/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosman <aosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:13:00 by aosman            #+#    #+#             */
/*   Updated: 2025/08/03 20:48:33 by aosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"


volatile sig_atomic_t g_ack_received = 0;

/**
 * @brief Signal handler for client. Processes acknowledgments from server.
 *
 * @param sig Signal type (unused)
 * @param info Signal information (unused)
 * @param context Unused context parameter
 */
static void client_handler(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
	g_ack_received = 1;
}

/**
 * @brief Sends a single bit to the server
 *
 * @param server_pid Target server PID
 * @param bit Bit value to send (0 or 1)
 */
static void send_bit(pid_t server_pid, int bit)
{
	g_ack_received = 0;

	// Send signal based on bit value
	if (kill(server_pid, bit ? SIGUSR2 : SIGUSR1) < 0) {
		ft_putstr_fd("Error sending signal\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}

	// Wait for acknowledgment with timeout
	while (!g_ack_received)
		pause();
}

/**
 * @brief Sends a full character to the server bit-by-bit (LSB first)
 *
 * @param server_pid Target server PID
 * @param c Character to send
 */
static void send_char(pid_t server_pid, char c)
{
	int i = 0;

	while (i < 8) {
		send_bit(server_pid, (c >> i) & 1);
		i++;
	}
}

int main(int argc, char **argv)
{
	struct sigaction sa;
	pid_t server_pid;

	// Validate arguments
	if (argc != 3) {
		ft_putstr_fd("Usage: ./client <server_pid> <message>\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}

	// Configure acknowledgment handler
	sa.sa_sigaction = client_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) < 0) {
		ft_putstr_fd("Error setting signal handler\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}

	// Convert PID and send message
	server_pid = ft_atoi(argv[1]);
	while (*argv[2])
		send_char(server_pid, *argv[2]++);

	// Send null terminator to indicate message end
	send_char(server_pid, '\0');

	return (0);
}
