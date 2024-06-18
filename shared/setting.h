#ifndef SETTING_H
#define SETTING_H

namespace Setting
{
    namespace Signal
    {

        namespace Buffer
        {
            constexpr int buffer_size = 4;
        }

        namespace Speed
        {
            constexpr int min = 0;
            constexpr int max = 240;
            constexpr int start = 0;
            constexpr int length = 8;
        }

        namespace Temperature
        {
            constexpr int min = -60;
            constexpr int max = 60;
            constexpr int start = 8;
            constexpr int length = 7;
        }

        namespace Battery
        {
            constexpr int min = 0;
            constexpr int max = 100;
            constexpr int start = 15;
            constexpr int length = 7;
        }

        namespace Blinker_Left
        {
            constexpr int start = 23;
            constexpr int length = 1;
        }

        namespace Blinker_Right
        {
            constexpr int start = 24;
            constexpr int length = 1;
        }

        namespace Blinker_Warning
        {
            constexpr int start = 25;
            constexpr int length = 1;
        }
    }
}

#endif
