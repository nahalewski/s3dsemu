cmake_minimum_required(VERSION 3.13)

# Include the Switch toolchain file from the correct path
include(/opt/devkitpro/cmake/Switch.cmake)

# Set the architecture and system name
set(CMAKE_SYSTEM_NAME NintendoSwitch)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# Set the compilers
set(CMAKE_C_COMPILER aarch64-none-elf-gcc)
set(CMAKE_CXX_COMPILER aarch64-none-elf-g++)

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
link_directories(${DEVKITPRO}/libnx/lib)

# Find necessary tools for creating NROs
find_program(NX_ELF2NRO_EXE elf2nro HINTS "${DEVKITPRO}/tools/bin")
find_program(NX_NACPTOOL_EXE nacptool HINTS "${DEVKITPRO}/tools/bin")

if(NOT NX_ELF2NRO_EXE OR NOT NX_NACPTOOL_EXE)
    message(FATAL_ERROR "Required tools (elf2nro or nacptool) not found. Please install switch-tools.")
endif()