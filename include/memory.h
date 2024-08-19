#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>

class Memory {
public:
    Memory();
    ~Memory();

    uint32_t Read32(uint32_t address);
    uint16_t Read16(uint32_t address);
    uint8_t  Read8(uint32_t address);

    void Write32(uint32_t address, uint32_t value);
    void Write16(uint32_t address, uint16_t value);
    void Write8(uint32_t address, uint8_t value);

private:
    uint8_t* ram;
};

#endif // MEMORY_H