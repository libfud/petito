#include "apu.hpp"

namespace nes {

uint8_t* APU::map_address(uint16_t address)
{
    uint8_t* dataptr = nullptr;
    auto mapped_address = address - APU_REG_HIGH;
    if (mapped_address <= PULSE_1_END)
    {
        dataptr = &pulse_1.raw_data[mapped_address];
    }
    else if (mapped_address <= PULSE_2_END)
    {
        dataptr = &pulse_2.raw_data[mapped_address - PULSE_2_START];
    }
    else if (mapped_address <= TRIANGLE_END)
    {
        dataptr = &triangle.raw_data[mapped_address - TRIANGLE_START];
    }
    else if (mapped_address <= NOISE_END)
    {
        dataptr = &noise.raw_data[mapped_address - NOISE_START];
    }
    else if (mapped_address <= DMC_END)
    {
        dataptr = &dmc.raw_data[mapped_address - DMC_START];
    }
    else if (mapped_address == STATUS_ADDR)
    {
        dataptr = &status;
    }
    else if (mapped_address == STATUS_ADDR)
    {
        dataptr = &status;
    }

    return dataptr;
}

uint8_t APU::read(uint16_t address)
{
    auto data = 0;
    auto data_ptr = map_address(address);
    if (data_ptr != nullptr)
    {
        data = *data_ptr;
    }
    return data;
}

void APU::write(uint16_t address, uint8_t data)
{
    auto data_ptr = map_address(address);
    if (data_ptr != nullptr)
    {
        *data_ptr = data;
    }
}

}
