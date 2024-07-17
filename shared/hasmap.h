#include <unordered_map>
#include <string>
#include <iostream>

// Define a structure to hold the configuration parameters
struct Setting
{
    int min;
    int max;
    int start;
    int length;
};

// Define the hash map to store these settings
std::unordered_map<std::string, Setting> settings_map = {
    {"Buffer::buffer_size", {4, 4, 0, 0}},
    {"Speed::min", {0, 0, 0, 0}},
    {"Speed::max", {240, 240, 0, 0}},
    {"Speed::start", {0, 0, 0, 0}},
    {"Speed::length", {8, 8, 0, 0}},
    {"Temperature::min", {-60, -60, 0, 0}},
    {"Temperature::max", {60, 60, 0, 0}},
    {"Temperature::start", {8, 8, 0, 0}},
    {"Temperature::length", {7, 7, 0, 0}},
    {"Battery::min", {0, 0, 0, 0}},
    {"Battery::max", {100, 100, 0, 0}},
    {"Battery::start", {15, 15, 0, 0}},
    {"Battery::length", {7, 7, 0, 0}},
    {"Blinker_Left::start", {22, 22, 0, 0}},
    {"Blinker_Left::length", {1, 1, 0, 0}},
    {"Blinker_Right::start", {23, 23, 0, 0}},
    {"Blinker_Right::length", {1, 1, 0, 0}},
    {"Blinker_Warning::start", {24, 24, 0, 0}},
    {"Blinker_Warning::length", {1, 1, 0, 0}}};

int main()
{
    // Example: Access a setting
    std::string key = "Speed::max";
    if (settings_map.find(key) != settings_map.end())
    {
        std::cout << "Max Speed: " << settings_map[key].max << std::endl;
    }
    else
    {
        std::cout << "Setting not found!" << std::endl;
    }
    return 0;
}