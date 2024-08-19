// gpu.cpp
#include "gpu.h"

GPU::GPU(Memory& mem) : memory(mem) {
    ClearFrameBuffer(0x000000);
}

void GPU::ExecuteCommand(uint32_t command) {
    if ((command & 0xF0000000) == 0x10000000) {
        ProcessDrawCommand(command);
    } else if ((command & 0xF0000000) == 0x20000000) {
        ProcessVertexCommand(command);
    } else if ((command & 0xF0000000) == 0x30000000) {
        ProcessShaderCommand(command);
    }
}

void GPU::ProcessDrawCommand(uint32_t command) {
    if (command == 0x10000000) {
        ClearFrameBuffer(0x000000);  // Clear to black
    } else if (command == 0x10000001) {
        uint32_t vertexData[9]; // 3 vertices for a triangle
        DrawTriangle(vertexData);
    }
}

void GPU::ProcessVertexCommand(uint32_t command) {
    uint32_t vertexAddress = command & 0x0FFFFFFF;
    uint32_t* vertexData = reinterpret_cast<uint32_t*>(memory.Read32(vertexAddress));
    // Process vertex data here
}

void GPU::ProcessShaderCommand(uint32_t command) {
    uint32_t shaderAddress = command & 0x0FFFFFFF;
    // Execute the shader from this address
}

void GPU::ClearFrameBuffer(uint32_t color) {
    for (int y = 0; y < 240; ++y) {
        for (int x = 0; x < 400; ++x) {
            framebuffer[y][x] = color;
        }
    }
}

void GPU::DrawTriangle(uint32_t* vertexData) {
    // Simple triangle rasterization
    // Implement basic triangle drawing algorithm (e.g., Bresenham's line algorithm)
}