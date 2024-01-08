TARGETS = $(patsubst %.c,%,$(wildcard *.c))

CC = gcc
CFLAGS = -Wall

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

# Lösche alle erzeugten Dateien
clean:
	rm -f $(TARGETS)
