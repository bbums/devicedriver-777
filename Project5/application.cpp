#include "device_driver.h"

class Application {
public:
	Application(DeviceDriver* dd) : dd{dd} {}

	void readAndPrint(long startAddr, long endAddr) {
		for (int addr = startAddr; addr <= endAddr; addr++) {
			int data = dd->read(addr);
			printf("[%c] ",data);
		}
		printf("\n");
	}

	void writeAll(int data) {
		for (int addr = 0; addr <= 4; addr++) {
			dd->write(addr, data);
		}
	}
private:
	DeviceDriver* dd;
};