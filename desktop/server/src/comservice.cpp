#include "comservice.h"
#include "setting.h"

COMService::~COMService() = default; // Define the virtual destructor

void COMService::set_Speed(int speed)
{
    std::lock_guard<std::mutex> lock(setter_mutex);
    buffer_insert(static_cast<uint32_t>(speed), Setting::Signal::Speed::start, Setting::Signal::Speed::length);
}

void COMService::set_Temp(int temp)
{
    std::lock_guard<std::mutex> lock(setter_mutex);
    buffer_insert(static_cast<uint32_t>(temp), Setting::Signal::Temperature::start, Setting::Signal::Temperature::length);
}

void COMService::set_battery_level(int percentage)
{
    std::lock_guard<std::mutex> lock(setter_mutex);
    buffer_insert(static_cast<uint32_t>(percentage), Setting::Signal::Battery::start, Setting::Signal::Battery::length);
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

void COMService::buffer_insert(uint32_t value, size_t bit_pos, size_t bit_length)
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
}