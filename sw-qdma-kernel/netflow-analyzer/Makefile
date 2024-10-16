CC ?= gcc

CFLAGS += -g
#CFLAGS += -O2 -fno-inline -Wall -Wstrict-prototypes
CFLAGS += -I. -I/usr/local/include/qdma -I../dma-utils -I../device-manager
CFLAGS += $(EXTRA_FLAGS)

NETFLOW-ANALYZER = netflow-analyzer
DMA-UTILS_OBJS := $(patsubst %.c,%.o,$(wildcard ../dma-utils/*.c))
DEVICE-MANAGER_OBJS := $(patsubst %.c,%.o,$(wildcard ../device-manager/*.c))
NETFLOW-ANALYZER_OBJS := $(patsubst %.c,%.o,$(wildcard *.c))
NETFLOW-ANALYZER_OBJS += $(DEVICE-MANAGER_OBJS)
# NETFLOW-ANALYZER_OBJS += $(DMA-UTILS_OBJS)

ifneq ($(CROSS_COMPILE_FLAG),)
	CC=$(CROSS_COMPILE_FLAG)gcc
endif

all: clean netflow-analyzer

netflow-analyzer: $(NETFLOW-ANALYZER_OBJS)
	@echo $(NETFLOW-ANALYZER_OBJS)
	$(CC) -pthread -lrt -o $@ $^ -laio -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE -D_LARGE_FILE_SOURCE

%.o: %.c
	$(CC) $(CFLAGS) -c -std=c99 -o $@ $< -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE -D_LARGE_FILE_SOURCE -D_AIO_AIX_SOURCE

clean:
	@rm -f *.o */*.o ../dma-utils/*.o
	@rm -f *.o */*.o ../device-manager/*.o
	rm -rf *.o *.bin $(NETFLOW-ANALYZER)