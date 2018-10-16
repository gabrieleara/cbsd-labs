# Some useful commands

RM_ALL = rm -f *.o *.exe *.so *.a

# Flags
CFLAGS += -Wall -pedantic -std=c99

.PHONY: main all clean pipe fifo pipe-debug fifo-debug all-debug

main: pipe

all: pipe fifo

all-debug: CFLAGS += -DMY_DEBUG -g -O0
all-debug: LDFLAGS += -g
all-debug: pipe fifo

pipe-debug: CFLAGS += -DMY_DEBUG -g -O0
pipe-debug: LDFLAGS += -g
pipe-debug: pipe

fifo-debug: CFLAGS += -DMY_DEBUG -g -O0
fifo-debug: LDFLAGS += -g
fifo-debug: fifo

clean:
	$(RM_ALL)

pipe: main_pipe.exe

fifo: main_fifo_producer.exe main_fifo_consumer.exe # myfifo

#myfifo:
#	mkfifo -m 666 myfifo

%.exe: %.o
	$(LINK.o) $^ -o $@
