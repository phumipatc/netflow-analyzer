#include <xrt.h>
#include <experimental/xrt_kernel.h>

class device
{
public:
	xrtDeviceHandle deviceHandler;
	/* data */

private:
	void chooseDevice(uint32_t* device_index);

public:
	device(/* args */);
	~device();

public:
	uint32_t Initialize(uint32_t* device_index);
	uint32_t Uninitialize();
};