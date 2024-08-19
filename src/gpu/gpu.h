// gpu.h
#ifndef GPU_H
#define GPU_H

#include <cstdint>
#include "memory.h"

class GPU {
public:
    GPU(Memory& memory);
    void ExecuteCommand(uint32_t command);

private:
    Memory& memory;  // Reference to system memory
    uint32_t framebuffer[240][400];  // Simple framebuffer for top screen

    void ProcessDrawCommand(uint32_t command);
    void ProcessVertexCommand(uint32_t command);
    void ProcessShaderCommand(uint32_t command);

    void ClearFrameBuffer(uint32_t color);
    void DrawTriangle(uint32_t* vertexData);
};

#endif // GPU_H