TARGETS = $(patsubst %.c,%,$(wildcard *.c))

CC = gcc

all: $(TARGETS)

%: %.c
	$(CC) -o $@ $<

# Lösche alle erzeugten Dateien
clean:
	rm -f $(TARGETS)
