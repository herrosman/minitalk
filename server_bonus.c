/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosman <aosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 21:08:48 by aosman            #+#    #+#             */
/*   Updated: 2025/08/10 20:39:58 by aosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

// Global variable to keep track of server state
static t_server g_data = {0, 0, 0, 0};

// Resets the server state to prepare for a new message or client
static void reset_server_state(void)
{
	g_data.current_char = 0;
	g_data.bit_count = 0;
	g_data.client_pid = 0;
	g_data.active = 0;
}

// Sends an acknowledgment signal (SIGUSR1) to the client
static void send_ack(pid_t pid)
{
	// If sending the signal fails, print an error and reset state
	if (kill(pid, SIGUSR1)) {
		ft_putstr_fd("Error sending acknowledgment\n", STDERR_FILENO);
		reset_server_state();
	}
}

// Called when a full character (32 bits) has been received
static void handle_character_completion(void)
{
	// If the character is 0, it's the end of the message
	if (g_data.current_char == 0) {
		// Send a final acknowledgment (SIGUSR2) to the client
		if (kill(g_data.client_pid, SIGUSR2)) {
			ft_putstr_fd("Error sending final ack\n", STDERR_FILENO);
		}
		reset_server_state(); // Prepare for a new message
		return;
	}
	// Otherwise, print the character (lowest byte) to the terminal
	unsigned char c = g_data.current_char & 0xFF;
	//ft_printf("[%02x]", c);
	write(STDOUT_FILENO, &c, 1);
	g_data.current_char = 0;
	g_data.bit_count = 0;
}

// Signal handler: called whenever a signal (SIGUSR1 or SIGUSR2) is received
static void server_handler(int sig, siginfo_t *info, void *context)
{
	(void)context; // Unused parameter

	// If no client is active, set the client PID and mark as active
	if (!g_data.active) {
		g_data.client_pid = info->si_pid;
		g_data.active = 1;
	}
	// If a different client sends a signal, ignore it
	else if (g_data.client_pid != info->si_pid) {
		return;
	}

	// Add the received bit to current_char
	// SIGUSR1 means bit 0, SIGUSR2 means bit 1
	g_data.current_char |= ((sig == SIGUSR2) << g_data.bit_count);
	g_data.bit_count++;

	// If we've received 8 bits, process the character
	if (g_data.bit_count == 8) {
		handle_character_completion();
	}

	// Send acknowledgment to the client for each bit received
	send_ack(info->si_pid);
}

int main(void)
{
	struct sigaction sa; // Structure to configure signal handling

	ft_printf("Server PID: %d\n", getpid()); // Print server PID for clients
	reset_server_state(); // Initialize server state

	// Set up signal handler for SIGUSR1 and SIGUSR2
	sa.sa_sigaction = server_handler; // Use our custom handler
	sa.sa_flags = SA_SIGINFO | SA_NODEFER; // Get extra info, don't block signals
	sigemptyset(&sa.sa_mask); // No signals are blocked during handler

	// Register the signal handlers
	if (sigaction(SIGUSR1, &sa, NULL) < 0 ||
		sigaction(SIGUSR2, &sa, NULL) < 0) {
		ft_putstr_fd("Error setting signal handlers\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}

	// Main loop: wait for signals forever
	while (1) pause();
	return (0);
}
