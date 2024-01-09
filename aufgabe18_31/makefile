CC = gcc

CFLAGS = -Wall -Wextra -std=c99

SOURCES = $(shell find . -type f -name "*.c")

TARGETS = $(SOURCES:.c=)

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGETS)

.PHONY: all clean
