#include <device.h>

device::device(/* args */) {
	deviceHandler = nullptr;
}

device::~device() {
	deviceHandler = nullptr;
}

void device::chooseDevice(uint32_t* device_index) {
	// enumerate devices
	uint32_t numDevices = xclProbe();
	if (numDevices == 0) {
		std::cerr << "No devices found." << std::endl;
	}
	std::cout << "Found " << numDevices << " device(s)." << std::endl;

	// List devices
	std::cout << "Multiple devices found...please choose device:" << std::endl;
	for (uint32_t i = 0; i < numDevices; i++) {
		// Open device
		xclDeviceHandle tempDeviceHandle = xclOpen(i, NULL, XCL_QUIET);

		if (tempDeviceHandle != nullptr) {
			// Get device name
			xclDeviceInfo2 deviceInfo;
			int res = xclGetDeviceInfo2(tempDeviceHandle, &deviceInfo);
			if (res == 0) {
				std::cout << "[" << i << "] " << deviceInfo.mName << std::endl;
			}
		}
	}
}

uint32_t device::Initialize(uint32_t* device_index) {
	chooseDevice(device_index);

	deviceHandler = xrtDeviceOpen(*device_index);
	if (!deviceHandler) {
		std::cerr << "Failed to open device." << std::endl;
		return 1;
	}
	std::cout << "Opened device successfully." << std::endl;
	return 0;
}

uint32_t device::Uninitialize() {
	if (deviceHandler) {
		int res = xrtDeviceClose(deviceHandler);
		return res;
	}
	return 0;
}