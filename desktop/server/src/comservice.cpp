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

    /* for (size_t i = 0; i < 4; ++i)
    {
        for (int j = 7; j >= 0; --j)
        {
            std::cout << ((buffer[i] >> j) & 1);
        }
        std::cout << " ";
    }
    std::cout << std::endl; */
}

void COMService::set_Temp(int temp)
{
    std::lock_guard<std::mutex> lock(setter_mutex);
    buffer_insert(static_cast<uint32_t>(temp), Setting::Signal::Temperature::start, Setting::Signal::Temperature::length);

    /* for (size_t i = 0; i < 4; ++i)
    {
        for (int j = 7; j >= 0; --j)
        {
            std::cout << ((buffer[i] >> j) & 1);
        }
        std::cout << " ";
    }
    std::cout << std::endl; */
}

void COMService::set_battery_level(int percentage)
{
    std::lock_guard<std::mutex> lock(setter_mutex);
    buffer_insert(static_cast<uint32_t>(percentage), Setting::Signal::Battery::start, Setting::Signal::Battery::length); // HERE IS A PROBLEM!!
    // Debug output to check the buffer content
    /*  for (size_t i = 0; i < 4; ++i)
     {
         for (int j = 7; j >= 0; --j)
         {
             std::cout << ((buffer[i] >> j) & 1);
         }
         std::cout << " ";
     }
     std::cout << std::endl; */
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

void COMService::buffer_insert(uint32_t value, size_t start_bit, size_t bit_length)
{
    size_t end_bit = start_bit + bit_length - 1;

    // Clear the target bits in the buffer
    for (size_t i = start_bit; i <= end_bit; ++i)
    {
        size_t byte_index = i / 8;
        size_t bit_index = i % 8;

        buffer[byte_index] &= ~(1 << (7 - bit_index)); // Clear the bit
    }

    // Place the number into the buffer
    for (size_t i = 0; i < bit_length; ++i)
    {
        size_t current_bit = start_bit + i;
        size_t byte_index = current_bit / 8;
        size_t bit_index = current_bit % 8;

        if (value & (1 << i))
        {
            buffer[byte_index] |= (1 << (7 - bit_index)); // Set the bit
        }
    }

    for (int i = 0; i < 4; ++i)
    {
        std::bitset<8> bits(buffer[i]);
        std::cout << bits << " ";
    }
    std::cout << std::endl;
}