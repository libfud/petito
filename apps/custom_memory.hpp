#include "memory.hpp"

#include <cstdint>
#include <vector>

namespace petito {

class CustomMemory : public Memory {

public:
    CustomMemory(uint16_t ramSize, uint16_t romSize, Memory& input, Memory& output);

    uint8_t read(uint16_t address) override;

    void write(uint16_t address, uint8_t data) override;

private:
    std::vector<uint8_t> ram;
    std::vector<uint8_t> rom;
    uint8_t inputRegister;
    Memory& inputPort;
    uint8_t outputRegister;
    Memory& outputPort;
};

}
