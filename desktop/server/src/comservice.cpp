#include "comservice.h"
#include "setting.h"
#include <iostream>
#include <algorithm>
#include <bitset>
#include <cstring>

COMService::~COMService() = default; // Define the virtual destructor

void COMService::set_Speed(int speed)
{
    std::lock_guard<std::mutex> lock(setter_mutex);
    buffer_insert(static_cast<uint32_t>(speed), Setting::Signal::Speed::start, Setting::Signal::Speed::length);

    for (size_t i = 0; i < 4; ++i)
    {
        for (int j = 7; j >= 0; --j)
        {
            std::cout << ((buffer[i] >> j) & 1);
        }
        std::cout << " ";
    }
    std::cout << std::endl;
}

void COMService::set_Temp(int temp)
{
    std::lock_guard<std::mutex> lock(setter_mutex);
    buffer_insert(static_cast<uint32_t>(temp), Setting::Signal::Temperature::start, Setting::Signal::Temperature::length);

    for (size_t i = 0; i < 4; ++i)
    {
        for (int j = 7; j >= 0; --j)
        {
            std::cout << ((buffer[i] >> j) & 1);
        }
        std::cout << " ";
    }
    std::cout << std::endl;
}

void COMService::set_battery_level(int percentage)
{
    std::lock_guard<std::mutex> lock(setter_mutex);
    buffer_insert(static_cast<uint32_t>(percentage), Setting::Signal::Battery::start, Setting::Signal::Battery::length); // HERE IS A PROBLEM!!
    // Debug output to check the buffer content
    for (size_t i = 0; i < 4; ++i)
    {
        for (int j = 7; j >= 0; --j)
        {
            std::cout << ((buffer[i] >> j) & 1);
        }
        std::cout << " ";
    }
    std::cout << std::endl;
}

void COMService::set_left_signal(bool signal)
{
    std::lock_guard<std::mutex> lock(setter_mutex);
    buffer_insert(static_cast<uint32_t>(signal), Setting::Signal::Blinker_Left::start, Setting::Signal::Blinker_Left::length);
}

void COMService::set_right_signal(bool signal)
{
    std::lock_guard<std::mutex> lock(setter_mutex);
    buffer_insert(static_cast<uint32_t>(signal), Setting::Signal::Blinker_Right::start, Setting::Signal::Blinker_Right::length);
}

void COMService::set_warning_signal(bool signal)
{
    std::lock_guard<std::mutex> lock(setter_mutex);
    buffer_insert(static_cast<uint32_t>(signal), Setting::Signal::Blinker_Warning::start, Setting::Signal::Blinker_Warning::length);
}

/* void COMService::buffer_insert(uint32_t value, size_t bit_pos, size_t bit_length)
{
    std::lock_guard<std::mutex> lock(buffer_mutex);
    size_t byte_pos = bit_pos / 8;
    size_t bit_offset = bit_pos % 8;

    value &= (1u << bit_length) - 1; // Mask to ensure only 'bit_length' bits are considered

    // Clear bits in buffer to be replaced
    for (size_t i = 0; i < (bit_length + 7) / 8; ++i)
    {
        buffer[byte_pos + i] &= ~(((1u << (8 - bit_offset)) - 1) << bit_offset); // Clear bits from bit_offset to end of byte
    }

    // Insert value into buffer
    for (size_t i = 0; i < (bit_length + 7) / 8; ++i)
    {
        buffer[byte_pos + i] |= static_cast<uint8_t>((value >> (i * 8)) << bit_offset); // Insert bits into buffer
    }
} */

void COMService::buffer_insert(uint32_t value, size_t start_bit, size_t bit_length)
{
    std::lock_guard<std::mutex> lock(buffer_mutex);

    // Ensure that the bit length is valid and fits within a single byte
    if (bit_length == 0 || start_bit + bit_length > 32)
    {
        std::cerr << "Invalid bit range or length" << std::endl;
        return;
    }

    // Place the value bit by bit
    for (size_t i = 0; i < bit_length; ++i)
    {
        // Calculate the bit index and the byte index
        int current_bit_index = start_bit + i;
        int byte_index = current_bit_index / 8;
        int bit_in_byte = current_bit_index % 8;

        // Clear the bit at the current position
        buffer[byte_index] &= ~(1 << bit_in_byte);

        // Set the bit with the current value bit
        if ((value & (1 << (bit_length - 1 - i))) != 0)
        {
            buffer[byte_index] |= (1 << bit_in_byte);
        }
    }
}
