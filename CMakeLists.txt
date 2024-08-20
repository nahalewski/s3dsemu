cmake_minimum_required(VERSION 3.28)
project(Switch3DSEmulator)

# Include the Switch toolchain file
include(C:/devkitPro/cmake/Switch.cmake)

# Set the architecture and system name
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# Set the compilers
set(CMAKE_C_COMPILER "C:/devkitPro/devkitA64/bin/aarch64-none-elf-gcc.exe")
set(CMAKE_CXX_COMPILER "C:/devkitPro/devkitA64/bin/aarch64-none-elf-g++.exe")

# Include directories
include_directories(
    C:/devkitPro/portlibs/switch/include
    include
)

# Link directories
link_directories(
    C:/devkitPro/portlibs/switch/lib
    C:/devkitPro/libnx/lib
)

# Set compiler flags
set(CMAKE_C_FLAGS "-g -Wall -O2 -ffunction-sections -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtp=soft -fPIE -D__SWITCH__")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fno-rtti -fno-exceptions")
set(CMAKE_ASM_FLAGS "-g -march=armv8-a+crc+crypto")
set(CMAKE_EXE_LINKER_FLAGS "-specs=C:/devkitPro/libnx/switch.specs -g -march=armv8-a+crc+crypto -Wl,-Map,${PROJECT_NAME}.map")

# Set source files
set(SOURCES
    src/main.cpp
    src/main.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} GLESv2 EGL nx)

# Generate the NRO file
nx_create_nro(${PROJECT_NAME}
    NACP_NAME "Switch 3DS Emulator"
    NACP_AUTHOR "Your Name"
    ICON_PATH "${CMAKE_SOURCE_DIR}/icon.jpg"
)
