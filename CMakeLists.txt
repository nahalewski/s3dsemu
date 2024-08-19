cmake_minimum_required(VERSION 3.13)
project(Switch3DSEmulator)

# Include the Switch toolchain file from the correct path
include(${DEVKITPRO}/cmake/Switch.cmake)

# Set the architecture and system name
set(CMAKE_SYSTEM_NAME NintendoSwitch)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# Set the compilers
find_program(CMAKE_C_COMPILER aarch64-none-elf-gcc HINTS ${DEVKITPRO}/devkitA64/bin)
find_program(CMAKE_CXX_COMPILER aarch64-none-elf-g++ HINTS ${DEVKITPRO}/devkitA64/bin)

# Set the linker and other settings
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
set(CMAKE_EXE_LINKER_FLAGS "-specs=${DEVKITPRO}/libnx/switch.specs -fPIE")
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_FLAGS "")

# Set the standard libraries to link against
set(CMAKE_C_STANDARD_LIBRARIES "-lnx -lm")
set(CMAKE_CXX_STANDARD_LIBRARIES "-lnx -lm")

# Define paths for includes and libraries
include_directories(${DEVKITPRO}/libnx/include)
include_directories(/opt/devkitpro/portlibs/switch/include/SDL2)
link_directories(${DEVKITPRO}/libnx/lib)
link_directories(/opt/devkitpro/portlibs/switch/lib)

# Add executable and source files
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

# Add custom command to create NRO file
add_custom_command(TARGET Switch3DSEmulator POST_BUILD
    COMMAND ${DEVKITPRO}/tools/bin/elf2nro
    ARGS --output ${CMAKE_BINARY_DIR}/Switch3DSEmulator.nro ${CMAKE_BINARY_DIR}/Switch3DSEmulator
    COMMENT "Generating NRO file"
)

# Ensure the custom command is executed after build
add_custom_target(generate_nro ALL DEPENDS Switch3DSEmulator)