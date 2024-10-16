#include <device_manager.h>
#include <netflow_receiver.h>

int main(int argc, char* argv[]) {
    DeviceManager dm;
    NetflowAnalyzer na;

    // Initialize DeviceManager
    if (DeviceManager_init(&dm) != 0) {
        fprintf(stderr, "Failed to initialize Device Manager\n");
        return -1;
    }

    // List devices and select one
    DeviceManager_list_devices(&dm);
    if (DeviceManager_select_device(&dm) != 0) {
        fprintf(stderr, "Failed to select device\n");
        DeviceManager_destructor(&dm);
        return -1;
    }

    // Initialize NetflowAnalyzer
    uint64_t buffer_size = 4096;  // Example buffer size
    uint64_t axi_address = 0x0;  // Example AXI address
    if (NetflowAnalyzer_init(&na, &dm, buffer_size, axi_address) != 0) {
        fprintf(stderr, "Failed to initialize NetFlow Analyzer\n");
        DeviceManager_close(&dm);
        DeviceManager_destructor(&dm);
        return -1;
    }

    // Receive packets
    uint64_t packet_count = 10;  // Example count
    NetflowAnalyzer_receive(&na, packet_count);

    // Cleanup
    NetflowAnalyzer_cleanup(&na);
    DeviceManager_close(&dm);
    DeviceManager_destructor(&dm);

    return 0;
}
