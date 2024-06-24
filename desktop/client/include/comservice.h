#ifndef COMSERVICE_H
#define COMSERVICE_H

#include <cstdint>
#include <cstring>
#include <atomic>
#include "setting.h"

// Abstract base class defining the communication service interface
class COMService
{
protected:
    std::atomic<bool> communication_status = false;

    uint8_t buffer[Setting::Signal::Buffer::buffer_size]{0}; // PROTECT WITH MUTEX

public:
    int get_speed();         // Read speed from the buffer
    int get_temperature();   // Read temperature from the buffer
    int get_battery_level(); // Read battery level from the buffer
    bool get_left_signal();
    bool get_right_signal();
    bool get_warning_signal();

    uint32_t buffer_extract(size_t bit_pos, size_t bit_length);

    bool get_status(); // Get the status of the communication

    virtual void run() = 0; // Receive the buffer over the communication protocol
    virtual ~COMService() = 0;
};

#endif // COMSERVICE_H
/*
void buffer_insert(uint8_t *buf, uint32_t value, size_t bit_pos, size_t bit_length)
{
    size_t byte_pos = bit_pos / 8;
    size_t bit_offset = bit_pos % 8;

    value &= (1u << bit_length) - 1; // Mask to ensure only 'bit_length' bits are considered

    // Clear bits in buffer to be replaced
    for (size_t i = 0; i < (bit_length + 7) / 8; ++i)
    {
        buf[byte_pos + i] &= ~(((1u << (8 - bit_offset)) - 1) << bit_offset); // Clear bits from bit_offset to end of byte
    }

    // Insert value into buffer
    for (size_t i = 0; i < (bit_length + 7) / 8; ++i)
    {
        buf[byte_pos + i] |= static_cast<uint8_t>((value >> (i * 8)) << bit_offset); // Insert bits into buffer
    }
} */
