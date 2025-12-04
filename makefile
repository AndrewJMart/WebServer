CC = gcc
CFLAGS = -Wall -Wextra -Iheaders

SRC = src/httpserver.c src/httpthread.c
OBJ = $(SRC:.c=.o)

TARGET = server

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# pattern rule for building .o from .c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: all
	sudo ./$(TARGET)

