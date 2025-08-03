/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosman <aosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 22:56:07 by aosman            #+#    #+#             */
/*   Updated: 2025/08/03 22:59:00 by aosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H
# include <signal.h>      // For signal handling functions
# include <unistd.h>      // For write(), pause(), etc.
# include <stdlib.h>      // For exit(), EXIT_FAILURE
# include "libft/libft.h" // Custom library for printing and string functions

// Structure to hold the server's state
typedef struct s_server {
	unsigned int    current_char; // Stores the bits received for the current character
	int             bit_count;    // Number of bits received so far for the character
	pid_t           client_pid;   // PID of the client currently communicating
	int             active;       // Flag: is a client currently active?
} t_server;
#endif
