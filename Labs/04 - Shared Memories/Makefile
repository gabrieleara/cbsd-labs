# Some useful commands

RM_ALL = rm -f *.o *.exe *.so *.a keyfile

# Flags
CFLAGS += -Wall -pedantic -std=c99

.PHONY: all clean server client

all: server client keyfile

all-debug: CFLAGS += -DMY_DEBUG -g -O0
all-debug: LDFLAGS += -g
all-debug: all

clean:
	$(RM_ALL)

server: main_server.exe

client: main_client.exe

%.exe: %.o
	$(LINK.o) $^ -o $@

keyfile:
	echo "This is an empty file which must exist for the ftok to function correctly," >> keyfile
	echo "see man ftok for further details." >> keyfile
