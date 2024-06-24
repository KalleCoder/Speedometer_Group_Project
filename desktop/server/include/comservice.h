#ifndef COMSERVICE_H
#define COMSERVICE_H
#include "setting.h"
#include <stdint.h>
#include <cstddef>

class COMService
{
protected:
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