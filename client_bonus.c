/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosman <aosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 21:09:24 by aosman            #+#    #+#             */
/*   Updated: 2025/08/03 22:58:02 by aosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

// These variables are used to track acknowledgments from the server.
// 'volatile' ensures they are updated correctly inside signal handlers.
volatile sig_atomic_t g_ack_received = 0;
volatile sig_atomic_t g_message_ack_received = 0;

// This function handles signals received from the server.
// SIGUSR1 means a bit was received, SIGUSR2 means the whole message was received.
static void client_handler(int sig)
{
	if (sig == SIGUSR1) {
		g_ack_received = 1; // Server acknowledged a bit
	} else if (sig == SIGUSR2) {
		g_message_ack_received = 1; // Server acknowledged the whole message
	}
}

// Sends a single bit to the server using signals.
// Retries if no acknowledgment is received.
static void send_bit(pid_t server_pid, int bit)
{
	int retry_count = 0;
	g_ack_received = 0; // Reset acknowledgment before sending

	while (!g_ack_received && retry_count < 100) {
		// Send SIGUSR1 for bit 0, SIGUSR2 for bit 1
		if (kill(server_pid, bit ? SIGUSR2 : SIGUSR1) < 0) {
			ft_putstr_fd("Error sending signal\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}

		// Wait for acknowledgment from server, with a timeout
		int timeout = 0;
		while (!g_ack_received && timeout < 10000) {
			usleep(10); // Sleep for 10 microseconds
			timeout++;
		}

		if (!g_ack_received) retry_count++; // Try again if not acknowledged
	}

	// If server never responds, print error and exit
	if (!g_ack_received) {
		ft_putstr_fd("Server not responding\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

// Sends a full character (as 32 bits) to the server, one bit at a time.
static void send_unicode_char(pid_t server_pid, unsigned int c)
{
	for (int i = 0; i < 32; i++) {
		send_bit(server_pid, (c >> i) & 1); // Send each bit, starting from least significant
	}
}

int main(int argc, char **argv)
{
	struct sigaction sa;
	pid_t server_pid;
	const char *msg;

	// Check for correct usage
	if (argc != 3) {
		ft_putstr_fd("Usage: ./client <server_pid> <message>\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}

	// Set up signal handler for acknowledgments from server
	sa.sa_handler = client_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);

	if (sigaction(SIGUSR1, &sa, NULL) < 0 ||
		sigaction(SIGUSR2, &sa, NULL) < 0) {
		ft_putstr_fd("Error setting signal handlers\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}

	// Get server PID and message from command line arguments
	server_pid = ft_atoi(argv[1]);
	msg = argv[2];

	// Send each byte of the message to the server as a 32-bit value
	size_t len = ft_strlen(msg);
	for (size_t i = 0; i < len; i++) {
		send_unicode_char(server_pid, (unsigned char)msg[i]);
	}

	// Send a null terminator to indicate end of message
	send_unicode_char(server_pid, '\0');

	// Wait for final acknowledgment from server (SIGUSR2)
	int timeout = 0;
	while (!g_message_ack_received && timeout < 5000) {
		usleep(100); // Sleep for 100 microseconds
		timeout++;
	}

	// Print result based on whether acknowledgment was received
	if (g_message_ack_received) {
		ft_printf("Message received by server!\n");
	} else {
		ft_printf("Server did not confirm receipt\n");
	}

	return (0);
}
