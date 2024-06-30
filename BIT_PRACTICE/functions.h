#include <iostream>
#include <bitset>

class Buffer
{
public:
    uint8_t buffer[4]{0};

    void insert(uint32_t number, size_t start_bit, size_t bit_length)
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

            if (number & (1 << i))
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

    uint32_t extract(size_t start_bit, size_t bit_length)
    {
        uint32_t result = 0;
        size_t end_bit = start_bit + bit_length - 1;

        // Extract bits from the buffer
        for (size_t i = 0; i < bit_length; ++i)
        {
            size_t current_bit = start_bit + i;
            size_t byte_index = current_bit / 8;
            size_t bit_index = current_bit % 8;

            if (buffer[byte_index] & (1 << (7 - bit_index)))
            {
                result |= (1 << i);
            }
        }

        return result;
    }
};