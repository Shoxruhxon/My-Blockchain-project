CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
SOURCES = my_blockchain.c
TARGET = my_blockchain
CC = gcc 

$(TARGET) : $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^
.PHONY:
	fclean

fclean:
	@rm -f $(OBJECTS) $(TARGET)