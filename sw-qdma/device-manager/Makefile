CC ?= gcc

CFLAGS += -g
#CFLAGS += -O2 -fno-inline -Wall -Wstrict-prototypes
CFLAGS += -I. -I/usr/local/include/qdma
CFLAGS += $(EXTRA_FLAGS)

all: device_manager.o

%.o: %.c
	$(CC) $(CFLAGS) -c -std=c99 -o $@ $< -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE -D_LARGE_FILE_SOURCE -D_AIO_AIX_SOURCE

clean:
	rm -rf *.o