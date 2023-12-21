# CC = gcc
# CFLAGS = -Wall -Wextra -g
Source = date_file.c main_file.c word_file.c
executable = $(patsubst %.c,%,$(Source))
all: $(executable)
clean:
	rm -f $(executable)

input = test1.txt
input1 = test2.txt
run: $(executable)
	./$(executable) < $(input) <$(input1)
