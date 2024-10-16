#ifndef NETFLOW_ANALYZER_H
#define NETFLOW_ANALYZER_H

#include "device_manager.h"

// Define buffer size for DMA
#define DMA_BUFFER_SIZE 4096

typedef struct {
    int active;
    int device_id;
    int device_fd;
    char *dma_buffer;
} NetflowAnalyzer;

// Constructor and Destructor
NetflowAnalyzer* create_netflow_analyzer(int device_id, int device_fd);
void destroy_netflow_analyzer(NetflowAnalyzer* na);

// Start and stop functions
void start_receiving(NetflowAnalyzer* na);
void stop_receiving(NetflowAnalyzer* na);

// Signal handling
void signal_handler(int sig);

#endif // NETFLOW_ANALYZER_H
