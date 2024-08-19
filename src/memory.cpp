// memory.cpp
#include "memory.h"
#include <cstdlib>
#include <cstring>

Memory::Memory() {
    // Initialize memory regions, example for 128MB of RAM
    ram = static_cast<uint8_t*>(std::malloc(128 * 1024 * 1024));
    std::memset(ram, 0, 128 * 1024 * 1024); // Clear RAM
}

Memory::~Memory() {
    std::free(ram);
}

uint32_t Memory::Read32(uint32_t address) {
    return *reinterpret_cast<uint32_t*>(ram + address);
}

uint16_t Memory::Read16(uint32_t address) {
    return *reinterpret_cast<uint16_t*>(ram + address);
}

uint8_t Memory::Read8(uint32_t address) {
    return *(ram + address);
}

void Memory::Write32(uint32_t address, uint32_t value) {
    *reinterpret_cast<uint32_t*>(ram + address) = value;
}

void Memory::Write16(uint32_t address, uint16_t value) {
    *reinterpret_cast<uint16_t*>(ram + address) = value;
}

void Memory::Write8(uint32_t address, uint8_t value) {
    *(ram + address) = value;
}