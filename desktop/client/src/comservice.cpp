#include "comservice.h"
#include "setting.h"

#include <cstdint>
#include <cstring>
#include <iostream>

COMService::~COMService() = default; // Define the virtual destructor

// Pure virtual functions for client side functionalities
int COMService::get_speed()
{
    std::lock_guard<std::mutex> lock(getter_mutex);

    uint32_t speed{0};

    extract(Setting::Signal::Speed::start, Setting::Signal::Speed::length, speed);

    return static_cast<int>(speed);
}

int COMService::get_temperature()
{
    std::lock_guard<std::mutex> lock(getter_mutex);

    int temperature{0};

    extract(Setting::Signal::Temperature::start, Setting::Signal::Temperature::length, temperature);

    return temperature;
}
int COMService::get_battery_level()
{
    std::lock_guard<std::mutex> lock(getter_mutex);

    uint32_t battery_level{0};

    extract(Setting::Signal::Battery::start, Setting::Signal::Battery::length, battery_level);

    return static_cast<int>(battery_level);
}
bool COMService::get_left_signal()
{
    std::lock_guard<std::mutex> lock(getter_mutex);

    uint32_t left_signal{0};

    extract(Setting::Signal::Blinker_Left::start, Setting::Signal::Blinker_Left::length, left_signal);

    return static_cast<bool>(left_signal);
}
bool COMService::get_right_signal()
{
    std::lock_guard<std::mutex> lock(getter_mutex);

    uint32_t right_signal{0};

    extract(Setting::Signal::Blinker_Right::start, Setting::Signal::Blinker_Right::length, right_signal);

    return static_cast<bool>(right_signal);
}

bool COMService::get_warning_signal()
{
    std::lock_guard<std::mutex> lock(getter_mutex);

    uint32_t warning_signal{0};

    extract(Setting::Signal::Blinker_Warning::start, Setting::Signal::Blinker_Warning::length, warning_signal);

    return static_cast<bool>(warning_signal);
}

bool COMService::get_status()
{
    return communication_status;
}

/* uint32_t COMService::buffer_extract(size_t bit_pos, size_t bit_length)
{
    uint32_t result = 0;

    // Extract bits from the buffer
    for (size_t i = 0; i < bit_length; ++i)
    {
        size_t current_bit = bit_pos + i;
        size_t byte_index = current_bit / 8;
        size_t bit_index = current_bit % 8;

        if (buffer[byte_index] & (1 << (7 - bit_index)))
        {
            result |= (1 << i);
        }
    }

    return result;
} */

void COMService::extract(size_t bit_pos, size_t bit_length, uint32_t &value)
{
    uint32_t result = 0;

    // Extract bits from the buffer
    for (size_t i = 0; i < bit_length; ++i)
    {
        size_t current_bit = bit_pos + i;
        size_t byte_index = current_bit / 8;
        size_t bit_index = current_bit % 8;

        if (buffer[byte_index] & (1 << (7 - bit_index)))
        {
            result |= (1 << i);
        }
    }

    value = result;
}

// for integers
void COMService::extract(size_t bit_pos, size_t bit_length, int &value)
{
    uint32_t result = 0;

    // Extract bits from the buffer
    for (size_t i = 0; i < bit_length; ++i)
    {
        size_t current_bit = bit_pos + i;
        size_t byte_index = current_bit / 8;
        size_t bit_index = current_bit % 8;

        if (buffer[byte_index] & (1 << (7 - bit_index)))
        {
            result |= (1 << i);
        }
    }

    uint32_t sign_bit = (result >> (Setting::Signal::Temperature::length - 1)) & 0x01;

    uint32_t magnitude_value = result & ((1u << (Setting::Signal::Temperature::length - 1)) - 1);

    value = (sign_bit != 0) ? -static_cast<int>((1u << (Setting::Signal::Temperature::length - 1)) - magnitude_value) : static_cast<int>(magnitude_value);
}
