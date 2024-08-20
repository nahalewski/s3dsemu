cmake_minimum_required(VERSION 3.13)

# Include the Switch toolchain file from the correct path
include(C:/devkitPro/cmake/Switch.cmake)

# Set the architecture and system name
set(CMAKE_SYSTEM_NAME NintendoSwitch)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# Set the compilers
set(CMAKE_C_COMPILER C:/devkitPro/devkitA64/bin/aarch64-none-elf-gcc.exe)
set(CMAKE_CXX_COMPILER C:/devkitPro/devkitA64/bin/aarch64-none-elf-g++.exe)

# Set the linker and other settings
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
set(CMAKE_EXE_LINKER_FLAGS "-specs=${DEVKITPRO}/libnx/switch.specs -fPIE")
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_FLAGS "")

# Include SDL2 directories
include_directories(${DEVKITPRO}/libnx/include)
include_directories(${DEVKITPRO}/portlibs/switch/include/SDL2)

# Link directories for SDL2
link_directories(${DEVKITPRO}/libnx/lib)
link_directories(${DEVKITPRO}/portlibs/switch/lib)

# Set up source files
add_executable(Switch3DSEmulator
    src/main.cpp
    src/cpu/arm11.cpp
    src/cpu/arm9.cpp
    src/input.cpp
    src/memory.cpp
    src/render.cpp
    src/gpu/gpu.cpp
)

# Link against libnx and SDL2 libraries
target_link_libraries(Switch3DSEmulator nx SDL2)

# Find necessary tools for creating NROs
find_program(NX_ELF2NRO_EXE elf2nro HINTS "${DEVKITPRO}/tools/bin")
find_program(NX_NACPTOOL_EXE nacptool HINTS "${DEVKITPRO}/tools/bin")

if(NOT NX_ELF2NRO_EXE OR NOT NX_NACPTOOL_EXE)
    message(FATAL_ERROR "Required tools (elf2nro or nacptool) not found. Please install switch-tools.")
endif()

# Generate the NRO file
add_custom_command(TARGET Switch3DSEmulator POST_BUILD
    COMMAND ${NX_ELF2NRO_EXE} Switch3DSEmulator.elf Switch3DSEmulator.nro
    COMMENT "Creating NRO file..."
)
