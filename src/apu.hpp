#ifndef APU_HPP
#define APU_HPP

#include <array>
#include <cstdint>
#include <vector>

namespace nes {

struct PulseChannel
{
    std::array<uint8_t, 4> raw_data;
};

struct TriangleChannel
{
    std::array<uint8_t, 4> raw_data;
};

struct NoiseChannel
{
    std::array<uint8_t, 4> raw_data;
};

struct DMC
{
    std::array<uint8_t, 4> raw_data;
};

class APU
{
private:
    static constexpr uint16_t APU_REG_HIGH = 0x4000;

    static constexpr uint8_t PULSE_1_END =    0x03;
    static constexpr uint8_t PULSE_2_START =  0x04;
    static constexpr uint8_t PULSE_2_END =    0x07;
    static constexpr uint8_t TRIANGLE_START = 0x08;
    static constexpr uint8_t TRIANGLE_END =   0x0B;
    static constexpr uint8_t NOISE_START =    0x0C;
    static constexpr uint8_t NOISE_END =      0x0F;
    static constexpr uint8_t DMC_START =      0x10;
    static constexpr uint8_t DMC_END =        0x13;
    static constexpr uint8_t STATUS_ADDR =    0x15;
    static constexpr uint8_t FC_ADDR =        0x17;

    PulseChannel pulse_1;
    PulseChannel pulse_2;
    TriangleChannel triangle;
    NoiseChannel noise;
    DMC dmc;

    uint8_t status;
    uint8_t frame_counter;

    uint8_t* map_address(uint16_t address);

public:
    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t data);

};

}

#endif
