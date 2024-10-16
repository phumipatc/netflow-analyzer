#include "netflow_receiver.h"
#include "dma_xfer_utils.c"  // Include the DMA utilities

int NetflowAnalyzer_init(NetflowAnalyzer *na, DeviceManager* dm, uint64_t size, uint64_t address) {
    na->deviceManager = dm;
    na->buffer_size = size;
    na->axi_address = address;
    na->verbose = 1;

    // Allocate aligned buffer for DMA
    if (posix_memalign((void**)&na->buffer, 4096, na->buffer_size + 4096) != 0) {
        fprintf(stderr, "Failed to allocate buffer\n");
        return -1;
    }
    return 0;
}

void NetflowAnalyzer_cleanup(NetflowAnalyzer *na) {
    if (na->buffer) {
        free(na->buffer);
    }
}

void NetflowAnalyzer_destructor(NetflowAnalyzer *na) {
    NetflowAnalyzer_cleanup(na);
}

void NetflowAnalyzer_receive(NetflowAnalyzer *na, uint64_t count) {
    ssize_t rc;
    struct timespec ts_start, ts_end;
    double total_time = 0, avg_time = 0;

    for (uint64_t i = 0; i < count; i++) {
        clock_gettime(CLOCK_MONOTONIC, &ts_start);

        // Use read_to_buffer from dma_xfer_utils.c to receive data
        rc = read_to_buffer(na->deviceManager->devname, na->deviceManager->fd, na->buffer, na->buffer_size, na->axi_address);
        if (rc < 0) {
            perror("Failed to read buffer");
            return;
        }

        clock_gettime(CLOCK_MONOTONIC, &ts_end);
        timespec_sub(&ts_end, &ts_start);
        total_time += (ts_end.tv_sec + ((double)ts_end.tv_nsec / NSEC_DIV));

        if (na->verbose) {
            printf("Received packet %lu: time = %ld.%09ld sec, size = %lu bytes\n", i, ts_end.tv_sec, ts_end.tv_nsec, na->buffer_size);
        }

        // Process the NetFlow packet
        processNetflowPacket(na->buffer, na->buffer_size);
    }

    avg_time = total_time / count;
    printf("Average reception time: %f sec\n", avg_time);
}

// Placeholder for processing NetFlow packets
void processNetflowPacket(char* buffer, uint64_t size) {
    // Implement packet processing logic her
}