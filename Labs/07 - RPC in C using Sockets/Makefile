# Some useful commands

RM_ALL = rm -f *.o *.exe *.so *.a

# Flags
CFLAGS += -Wall -pedantic -std=c99

.PHONY: all clean server client

all: server client

all-debug: CFLAGS += -DMY_DEBUG -g -O0
all-debug: LDFLAGS += -g
all-debug: all

clean:
	$(RM_ALL)

server: main_server.exe
client: main_client.exe

main_server.exe: main_server.o librpc_server.o
	$(LINK.o) $^ -o $@

main_client.exe: main_client.o librpc_client.o
	$(LINK.o) $^ -o $@

#%.exe: %.o
#	$(LINK.o) $^ -o $@
