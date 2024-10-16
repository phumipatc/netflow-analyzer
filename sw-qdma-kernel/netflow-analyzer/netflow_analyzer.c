#include "netflow_analyzer.h"
#include "dma_xfer_utils.c"  // Include the DMA utility functions
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

NetflowAnalyzer* netflow_analyzer_instance = NULL;  // Global instance for signal handling

NetflowAnalyzer* create_netflow_analyzer(int device_id, int device_fd) {
    NetflowAnalyzer* na = (NetflowAnalyzer*)malloc(sizeof(NetflowAnalyzer));
    if (!na) {
        fprintf(stderr, "Error: Could not allocate memory for NetflowAnalyzer.\n");
        return NULL;
    }
    na->device_id = device_id;
    na->device_fd = device_fd;
    na->dma_buffer = (char*)malloc(DMA_BUFFER_SIZE);
    na->active = 1;
    return na;
}

void destroy_netflow_analyzer(NetflowAnalyzer* na) {
    if (na) {
        if (na->dma_buffer) {
            free(na->dma_buffer);
        }
        free(na);
    }
}

void signal_handler(int sig) {
    if (sig == SIGINT && netflow_analyzer_instance != NULL) {
        printf("\nReceived Ctrl + C (SIGINT). Stopping netflow receiver...\n");
        netflow_analyzer_instance->active = 0;
    }
}

void start_receiving(NetflowAnalyzer* na) {
    printf("Starting Netflow Receiver on device %d (fd: %d)...\n", na->device_id, na->device_fd);
    signal(SIGINT, signal_handler);  // Set up signal handler for Ctrl + C
    netflow_analyzer_instance = na;  // Set the global instance for signal handling

    uint64_t base = 0;
    ssize_t rc;
    
    // Simulate continuous reception
    while (na->active) {
        printf("Reading data from device %d using DMA...\n", na->device_id);

        // Read data into the DMA buffer from the device file descriptor
        rc = read_to_buffer("netflow_device", na->device_fd, na->dma_buffer, DMA_BUFFER_SIZE, base);
        if (rc < 0) {
            fprintf(stderr, "Error: DMA read failed. Error code: %zd\n", rc);
            perror("DMA read");
            break;
        }

        // Process the received data (simulated here as printing the size of the received data)
        printf("Received %zd bytes of data.\n", rc);

        // In real implementation, additional processing of the received data would be done here
        base += rc;  // Increment base for next read

        sleep(1);  // Simulating some delay for continuous data reception
    }

    printf("Netflow Receiver stopped.\n");
}

void stop_receiving(NetflowAnalyzer* na) {
    na->active = 0;
}
