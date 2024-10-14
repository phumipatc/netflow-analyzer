#include <iostream>
#include <fstream>
#include <vector>
#include <csignal>

#include <device.h>

#include <xrt.h>
#include <experimental/xrt_kernel.h>

#define DATA_SIZE 1024

bool running = true;

// Signal handler to stop the loop when CTRL+C is pressed
void signal_handler(int signum) {
    std::cout << "\nTerminating transfer..." << std::endl;
    running = false;
}

int main(int argc, char** argv) {
    // Register signal handler to catch termination signals
    std::signal(SIGINT, signal_handler);	//CTRL-C
	std::signal(SIGTSTP, signal_handler);	//CTRL-Z

    // 1. Initialize the device
    device dev;
    uint32_t device_index = 0;
    if (dev.Initialize(&device_index) != 0) {
        return 1;
    }
    xrtDeviceHandle device = dev.deviceHandler;

    // 2. Allocate memory buffer on the host side
    xrtBufferHandle output_buffer_handle = xrtBOAlloc(device, DATA_SIZE, 0, XRT_BO_FLAGS_NONE);
    auto output_buffer = xrtBOMap(output_buffer_handle);  // Map the buffer into host address space
    if (!output_buffer) {
        std::cerr << "Failed to map output buffer." << std::endl;
        return 1;
    }
    std::cout << "Host output buffer allocated and mapped." << std::endl;

    // 3. Set up QDMA kernel handle (Assume the kernel is already loaded on the FPGA)
    xrtKernelHandle qdma_kernel_handle = xrtPLKernelOpen(device, nullptr, "qdma_kernel");
    if (!qdma_kernel_handle) {
        std::cerr << "Failed to open QDMA kernel." << std::endl;
        return 1;
    }
    std::cout << "QDMA kernel opened successfully." << std::endl;

    // 4. Continuously transfer data from card to host using QDMA
    std::cout << "Starting continuous data transfer..." << std::endl;

    while (running) {
        // Set up and run QDMA execution on the FPGA device
        xrtRunHandle qdma_run_handle = xrtKernelRun(qdma_kernel_handle, output_buffer_handle, DATA_SIZE);
        xrtRunWait(qdma_run_handle);  // Wait for completion of the transfer

        // Process the received data (optional)
        std::cout << "Received data:" << std::endl;
        for (int i = 0; i < DATA_SIZE; ++i) {
            std::cout << std::hex << output_buffer[i] << " ";
        }

        // Close the run handle for this iteration
        xrtRunClose(qdma_run_handle);
    }

    // 5. Clean up resources after loop ends
    xrtKernelClose(qdma_kernel_handle);
    xrtBOFree(output_buffer_handle);
    xrtDeviceClose(device);
    std::cout << "Resources cleaned up and application finished." << std::endl;

    return 0;
}
