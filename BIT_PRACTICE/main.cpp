#include "functions.h"

int main(void)
{
    Buffer buf;

    int length = 4;

    buf.insert(static_cast<uint32_t>(-11), 5, 4);

    uint32_t value = buf.extract(5, 4);

    std::cout << "Extracted number (decimal): " << value << std::endl;

    uint32_t sign_bit = (value >> (length - 1)) & 0x01;

    uint32_t magnitude_value = value & ((1u << (length - 1)) - 1);

    int temperature = (sign_bit != 0) ? -static_cast<int>((1u << (length - 1)) - magnitude_value) : static_cast<int>(magnitude_value);

    std::cout << "The value is: " << temperature << std::endl;
}