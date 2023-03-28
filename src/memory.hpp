#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstdint>

class Memory
{
public:
    // virtual ~Memory() = 0;

    /* Reads a byte of data from the data bus. */
    virtual uint8_t read(uint16_t address) = 0;

    /* Writes a byte of data to the data bus. */
    virtual void write(uint16_t address, uint8_t data) = 0;

};

#endif
