#ifndef NETFLOW_ANALYZER_H
#define NETFLOW_ANALYZER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "device_manager.h"

// NetflowAnalyzer structure
typedef struct {
    DeviceManager* deviceManager;
    char* buffer;
    uint64_t buffer_size;
    uint64_t axi_address;
    int verbose;
} NetflowAnalyzer;

// Function declarations
int NetflowAnalyzer_init(NetflowAnalyzer *na, DeviceManager* dm, uint64_t size, uint64_t address);
void NetflowAnalyzer_cleanup(NetflowAnalyzer *na);
void NetflowAnalyzer_destructor(NetflowAnalyzer *na);
void NetflowAnalyzer_receive(NetflowAnalyzer *na, uint64_t count);
void processNetflowPacket(char* buffer, uint64_t size);

#endif // NETFLOW_ANALYZER_H
