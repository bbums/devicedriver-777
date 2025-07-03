#include "device_driver.h"

#define START_READ_INDEX 2
#define END_READ_INDEX 5
#define MSG_READ_EXCEPTION "Read Fail Exception"
#define MSG_WRITE_EXCEPTION "Write Fail Exception"
#define STATUS_AVAILABLE 0xFF

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

int DeviceDriver::read(long address)
{
    int data = (int)(m_hardware->read(address));
    for (int i = START_READ_INDEX; i <= END_READ_INDEX; i++) {
        if ((int)(m_hardware->read(address)) != data) 
            throw ReadFailException(MSG_READ_EXCEPTION);
    }
    return data;
}

void DeviceDriver::write(long address, int data)
{
    if ((int)m_hardware->read(address) == STATUS_AVAILABLE)
        m_hardware->write(address, (unsigned char)data);
    else
        throw WriteFailException(MSG_WRITE_EXCEPTION);
}