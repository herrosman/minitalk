# Compiler settings
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a

# Targets
SERVER = server
CLIENT = client
SERVER_B = server_bonus
CLIENT_B = client_bonus

# Bonus mode switch
BONUS = 0

# Source files
ifeq ($(BONUS),1)
    SRC_SERVER = server_bonus.c
    SRC_CLIENT = client_bonus.c
    SERVER_EXEC = $(SERVER_B)
    CLIENT_EXEC = $(CLIENT_B)
else
    SRC_SERVER = server.c
    SRC_CLIENT = client.c
    SERVER_EXEC = $(SERVER)
    CLIENT_EXEC = $(CLIENT)
endif

OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

# Build rules
all: $(LIBFT) $(SERVER_EXEC) $(CLIENT_EXEC)

$(SERVER_EXEC): $(OBJ_SERVER) $(LIBFT)
	$(CC) $(CFLAGS) $< -o $@ -Llibft -lft

$(CLIENT_EXEC): $(OBJ_CLIENT) $(LIBFT)
	$(CC) $(CFLAGS) $< -o $@ -Llibft -lft

$(LIBFT):
	@make -C libft

bonus:
	@make BONUS=1

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C libft
	@rm -f $(OBJ_SERVER) $(OBJ_CLIENT) server.o client.o server_bonus.o client_bonus.o

fclean: clean
	@make fclean -C libft
	@rm -f $(SERVER) $(CLIENT) $(SERVER_B) $(CLIENT_B)

re: fclean all

.PHONY: all clean fclean re bonus
