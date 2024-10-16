#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// DeviceManager structure
typedef struct {
    int fd;
    char* devname;
    char** available_devices;
    int num_devices;
} DeviceManager;

// Function declarations
int DeviceManager_init(DeviceManager *dm);
void DeviceManager_close(DeviceManager *dm);
void DeviceManager_destructor(DeviceManager *dm);
void DeviceManager_list_devices(DeviceManager *dm);
int DeviceManager_open_device(DeviceManager *dm, const char* dev);
int DeviceManager_select_device(DeviceManager *dm);
int DeviceManager_prompt_user(DeviceManager *dm, const char* prompt);

#endif // DEVICE_MANAGER_H
