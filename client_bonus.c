/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosman <aosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 21:09:24 by aosman            #+#    #+#             */
/*   Updated: 2025/08/10 21:26:11 by aosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

// Only one global variable allowed: use this to track acknowledgment state.
// 0 = no ack, 1 = bit ack (SIGUSR1), 2 = message ack (SIGUSR2)
volatile sig_atomic_t	g_ack_state = 0;

// Signal handler for responses from the server.
// SIGUSR1: server received a bit, SIGUSR2: server received the whole message.
static void client_handler(int sig)
{
	if (sig == SIGUSR1) {
		g_ack_state = 1; // Server acknowledged a bit
	} else if (sig == SIGUSR2) {
		g_ack_state = 2; // Server acknowledged the whole message
	}
}

// Sends a single bit to the server using signals (SIGUSR1 for 0, SIGUSR2 for 1).
// Retries sending if no acknowledgment is received from the server.
static void send_bit(pid_t server_pid, int bit)
{
	int retry_count = 0;

	// If final ack already received, don't send more bits
	if (g_ack_state == 2)
		return;

	while (g_ack_state != 1 && g_ack_state != 2 && retry_count < 100) {
		if (kill(server_pid, bit ? SIGUSR2 : SIGUSR1) < 0) {
			ft_putstr_fd("Error sending signal\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		int timeout = 0;
		while (g_ack_state != 1 && g_ack_state != 2 && timeout < 10000) {
			usleep(10);
			timeout++;
		}
		if (g_ack_state != 1 && g_ack_state != 2)
			retry_count++;
	}

	if (g_ack_state != 1 && g_ack_state != 2) {
		ft_putstr_fd("Server not responding\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (g_ack_state == 1)
		g_ack_state = 0;
	// If g_ack_state == 2, do NOT reset it!
}

// Sends a single byte (8 bits) to the server, one bit at a time.
static void send_byte(pid_t server_pid, unsigned char c)
{
	for (int i = 0; i < 8; i++) {
		send_bit(server_pid, (c >> i) & 1); // Send each bit, starting from least significant
	}
}

int main(int argc, char **argv)
{
	struct sigaction sa;    // Used to set up signal handling
	pid_t server_pid;       // PID of the server process to send signals to
	const char *msg;        // Message to send

	// Check for correct usage: program expects 2 arguments (server PID and message)
	if (argc != 3) {
		ft_putstr_fd("Usage: ./client <server_pid> <message>\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}

	// Set up signal handler for acknowledgments from server
	sa.sa_handler = client_handler; // Function to call on signal
	sa.sa_flags = 0;                // No special flags
	sigemptyset(&sa.sa_mask);       // No signals are blocked during handler

	// Register the signal handlers for SIGUSR1 and SIGUSR2
	if (sigaction(SIGUSR1, &sa, NULL) < 0 ||
		sigaction(SIGUSR2, &sa, NULL) < 0) {
		ft_putstr_fd("Error setting signal handlers\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}

	// Get server PID and message from command line arguments
	server_pid = ft_atoi(argv[1]);
	msg = argv[2];

	g_ack_state = 0; // Reset acknowledgment state before sending

	// Send each byte of the message to the server as 8 bits
	size_t len = ft_strlen(msg);
	for (size_t i = 0; i < len; i++) {
		send_byte(server_pid, (unsigned char)msg[i]);
	}
	// Send a null terminator to indicate end of message
	send_byte(server_pid, '\0');

	// Wait for final acknowledgment from server (SIGUSR2)
	int timeout = 0;
	while (g_ack_state != 2 && timeout < 5000) {
		usleep(100); // Sleep for 100 microseconds to avoid busy waiting
		timeout++;
	}

	// Print result based on whether acknowledgment was received
	if (g_ack_state == 2) {
		ft_printf("Message received by server!\n");
	} else {
		ft_printf("Server did not confirm receipt\n");
	}
	return 0;
}
