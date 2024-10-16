#include "device_manager.h"

int DeviceManager_init(DeviceManager *dm) {
    // Simulate available devices
    dm->available_devices = (char**)malloc(3 * sizeof(char*));
    dm->available_devices[0] = strdup("/dev/xdma0");
    dm->available_devices[1] = strdup("/dev/xdma1");
    dm->available_devices[2] = strdup("/dev/xdma2");
    dm->num_devices = 3;
    dm->devname = NULL;
    dm->fd = -1;
    return 0;
}

void DeviceManager_destructor(DeviceManager *dm) {
    // Free device names
    for (int i = 0; i < dm->num_devices; i++) {
        free(dm->available_devices[i]);
    }
    free(dm->available_devices);
}

void DeviceManager_list_devices(DeviceManager *dm) {
    printf("Available devices:\n");
    for (int i = 0; i < dm->num_devices; i++) {
        printf("[%d] %s\n", i, dm->available_devices[i]);
    }
}

int DeviceManager_open_device(DeviceManager *dm, const char* dev) {
    dm->devname = strdup(dev);
    dm->fd = open(dm->devname, O_RDWR | O_NONBLOCK);
    if (dm->fd < 0) {
        perror("Failed to open device");
        return -1;
    }
    return 0;
}

void DeviceManager_close(DeviceManager *dm) {
    if (dm->fd > 0) {
        close(dm->fd);
        dm->fd = -1;
    }
    if (dm->devname) {
        free(dm->devname);
        dm->devname = NULL;
    }
}

int DeviceManager_select_device(DeviceManager *dm) {
    int choice = DeviceManager_prompt_user(dm, "Select device index:");
    if (choice < 0 || choice >= dm->num_devices) {
        fprintf(stderr, "Invalid device selection!\n");
        return -1;
    }
    return DeviceManager_open_device(dm, dm->available_devices[choice]);
}

int DeviceManager_prompt_user(DeviceManager *dm, const char* prompt) {
    int choice;
    printf("%s ", prompt);
    scanf("%d", &choice);
    return choice;
}
