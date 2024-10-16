#include "device_manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>


DeviceManager* create_device_manager() {
    DeviceManager* dm = (DeviceManager*)malloc(sizeof(DeviceManager));
    if (!dm) {
        fprintf(stderr, "Error: Could not allocate memory for DeviceManager.\n");
        return NULL;
    }
    dm->num_devices = 0;
    return dm;
}

void destroy_device_manager(DeviceManager* dm) {
    if (dm) {
        free(dm);
    }
}

int list_devices(DeviceManager* dm) {
    
    if (!dm) return -1;

    // Discover devices using dmactl


    // List available devices
    printf("Available devices:\n");
    for (int i = 0; i < dm->num_devices; i++) {
        printf("%d: %s (Path: %s)\n", dm->devices[i].id, dm->devices[i].name, dm->devices[i].path);
    }

    return 0;
}

int prompt_user(DeviceManager* dm) {
    if (!dm || dm->num_devices == 0) {
        fprintf(stderr, "Error: No devices available to select.\n");
        return -1;
    }

    int selected_device_id;
    printf("Enter the device ID you want to use: ");
    if (scanf("%d", &selected_device_id) != 1) {
        fprintf(stderr, "Error: Invalid input.\n");
        return -1;
    }

    if (selected_device_id < 0 || selected_device_id >= dm->num_devices) {
        fprintf(stderr, "Error: Invalid device ID.\n");
        return -1;
    }

    // Select the device
    if (select_device(dm, selected_device_id) != 0) {
        return -1;
    }

    return 0;
}

int select_device(DeviceManager* dm, int device_id) {
    if (!dm || device_id < 0 || device_id >= dm->num_devices) {
        fprintf(stderr, "Error: Invalid device ID for selection.\n");
        return -1;
    }

    printf("Selected device: %s (Path: %s)\n", dm->devices[device_id].name, dm->devices[device_id].path);
    return 0;
}

int open_device(DeviceManager* dm, int device_id) {
    if (!dm || device_id < 0 || device_id >= dm->num_devices) {
        fprintf(stderr, "Error: Invalid device ID for opening.\n");
        return -1;
    }

    int fd = open(dm->devices[device_id].path, O_RDWR);
    if (fd < 0) {
        fprintf(stderr, "Error: Could not open device %s. Error code: %d\n", dm->devices[device_id].path, errno);
        perror("open_device");
        return -1;
    }

    printf("Device %s opened successfully (FD: %d)\n", dm->devices[device_id].name, fd);
    return fd;  // Return the file descriptor
}

int close_device(DeviceManager* dm, int device_id) {
    if (!dm || device_id < 0 || device_id >= dm->num_devices) {
        fprintf(stderr, "Error: Invalid device ID for closing.\n");
        return -1;
    }

    int fd = open_device(dm, device_id);  // Retrieve FD (in practice, FD might be stored and retrieved differently)
    if (fd < 0) return -1;

    if (close(fd) < 0) {
        fprintf(stderr, "Error: Could not close device %s. Error code: %d\n", dm->devices[device_id].path, errno);
        perror("close_device");
        return -1;
    }

    printf("Device %s closed successfully.\n", dm->devices[device_id].name);
    return 0;
}
