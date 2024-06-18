#ifndef COMSERVICE_H
#define COMSERVICE_H
#include "setting.h"
#include <stdint.h>
#include <cstddef>

class COMService
{
private:
    uint8_t buffer[Setting::Signal::Buffer::buffer_size]{0};

public:
    void set_Speed(int speed);

    void set_Temp(int temp);

    void set_battery_level(int percentage);

    void set_left_signal(bool signal);

    void set_right_signal(bool signal);

    void set_warning_signal(bool signal);

    void buffer_insert(uint32_t value, size_t bit_pos, size_t bit_length);

    virtual void run() = 0;

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