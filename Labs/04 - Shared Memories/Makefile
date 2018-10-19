# Some useful commands

RM_ALL = rm -f *.o *.exe *.so *.a keyfile

# Flags
CFLAGS += -Wall -pedantic -std=c99

.PHONY: all clean server client producer consumer

all: server client keyfile producer consumer

all-debug: CFLAGS += -DMY_DEBUG -g -O0
all-debug: LDFLAGS += -g
all-debug: all

clean:
	$(RM_ALL)

server: main_server.exe keyfile
client: main_client.exe keyfile
producer: main_producer.exe keyfile
consumer: main_consumer.exe keyfile

%.exe: %.o
	$(LINK.o) $^ -o $@

main_producer.exe: main_producer.o shmlib.o
	$(LINK.o) $^ -o $@ -lpthread

main_consumer.exe: main_consumer.o shmlib.o
	$(LINK.o) $^ -o $@ -lpthread

keyfile:
	echo "This is an empty file which must exist for the ftok to function correctly," >> keyfile
	echo "see man ftok for further details." >> keyfile
