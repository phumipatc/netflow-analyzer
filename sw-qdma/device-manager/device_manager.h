#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#define MAX_DEVICES 10

typedef struct {
    int id;         // Unique identifier for the device
    char name[256]; // Human-readable name of the device
    char path[256]; // File path to the device (for example, /dev/qdma0)
} Device;

typedef struct {
    Device devices[MAX_DEVICES];
    int num_devices;  // Total number of devices found
} DeviceManager;

// Constructor and Destructor
DeviceManager* create_device_manager();
void destroy_device_manager(DeviceManager* dm);

// Device operations
int list_devices(DeviceManager* dm);
int prompt_user(DeviceManager* dm);
int select_device(DeviceManager* dm, int device_id);
int open_device(DeviceManager* dm, int device_id);
int close_device(DeviceManager* dm, int device_id);

#endif // DEVICE_MANAGER_H
