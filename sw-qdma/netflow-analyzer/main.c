#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "device_manager.h"
#include "netflow_analyzer.h"
#include <errno.h>

int main() {
    // Step 1: Create a DeviceManager and list available devices
    DeviceManager* dm = create_device_manager();
    if (dm == NULL) {
        fprintf(stderr, "Error: Failed to create device manager.\n");
        return -1;
    }

    if (list_devices(dm) < 0) {
        destroy_device_manager(dm);
        return -1;
    }

    // Step 2: Prompt the user to select a device
    if (prompt_user(dm) < 0) {
        fprintf(stderr, "Error: Failed to select device.\n");
        destroy_device_manager(dm);
        return -1;
    }

    int selected_device_id = dm->devices[0].id;  // Example: using the first device by default
    const char* device_path = dm->devices[0].path;  // Path to the device

    // Step 3: Open the selected device
    int device_fd = open_device(dm, selected_device_id);
    if (device_fd < 0) {
        destroy_device_manager(dm);
        return -1;
    }

    // Step 4: Create and start the NetflowAnalyzer on the selected device
    NetflowAnalyzer* na = create_netflow_analyzer(selected_device_id, device_fd);
    if (na == NULL) {
        fprintf(stderr, "Error: Failed to create netflow analyzer.\n");
        close(device_fd);
        destroy_device_manager(dm);
        return -1;
    }

    start_receiving(na);  // Start receiving netflow data using DMA

    // Step 5: Clean up after receiving is done (Ctrl + C is pressed)
    destroy_netflow_analyzer(na);
    close(device_fd);
    destroy_device_manager(dm);

    return 0;
}
