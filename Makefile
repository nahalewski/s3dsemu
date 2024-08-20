#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>/devkitpro")
endif

TOPDIR ?= $(CURDIR)
include $(DEVKITPRO)/libnx/switch_rules

#---------------------------------------------------------------------------------
# Project settings
#---------------------------------------------------------------------------------
TARGET      := Switch3DSEmulator
BUILD       := build
SOURCES     := src
INCLUDES    := include $(DEVKITPRO)/libnx/include $(DEVKITPRO)/portlibs/switch/include $(DEVKITPRO)/libnx/include/switch/nvidia
ROMFS       := romfs
ICON        := icon.jpg

#---------------------------------------------------------------------------------
# Compilation settings
#---------------------------------------------------------------------------------
ARCH        := -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtp=soft -fPIE
CFLAGS      := -g -Wall -O2 -ffunction-sections $(ARCH) $(DEFINES) \
               -I$(DEVKITPRO)/libnx/include \
               -I$(DEVKITPRO)/portlibs/switch/include \
               -I$(DEVKITPRO)/libnx/include/switch/nvidia \
               -D__SWITCH__
CXXFLAGS    := $(CFLAGS) -fno-rtti -fno-exceptions
ASFLAGS     := -g $(ARCH)
LDFLAGS     := -g -specs=$(DEVKITPRO)/libnx/switch.specs -Wl,-Map,$(TARGET).map -Wl,--allow-multiple-definition
LIBS        := -lnx -lEGL -lGLESv2 -lglapi -ldrm_nouveau -lSDL2 -lvulkan -lswitch

#---------------------------------------------------------------------------------
# Directories containing libraries
#---------------------------------------------------------------------------------
LIBDIRS     := $(DEVKITPRO)/libnx/lib $(DEVKITPRO)/portlibs/switch/lib $(DEVKITPRO)/libdrm_nouveau/lib
LIBPATHS    := $(foreach dir,$(LIBDIRS),-L$(dir))

#---------------------------------------------------------------------------------
# Build settings
#---------------------------------------------------------------------------------
export OUTPUT       := $(CURDIR)/$(TARGET)
export VPATH        := $(foreach dir,$(SOURCES),$(CURDIR)/$(dir))
export DEPSDIR      := $(CURDIR)/$(BUILD)

CFILES      := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES    := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES      := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
OFILES      := $(addprefix $(BUILD)/, $(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s:.o))

#---------------------------------------------------------------------------------
# Default build target
#---------------------------------------------------------------------------------
all: $(BUILD) $(TARGET).nro

$(BUILD):
	@mkdir -p $(BUILD)/src
	@mkdir -p $(BUILD)/include

#---------------------------------------------------------------------------------
# Clean up build files
#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(BUILD) $(TARGET).nro $(TARGET).nacp $(TARGET).elf

#---------------------------------------------------------------------------------
# Build targets
#---------------------------------------------------------------------------------
$(TARGET).nro: $(TARGET).elf
	@elf2nro $< $@ --icon=$(ICON) --nacp=$(TARGET).nacp --romfsdir=$(ROMFS)

$(TARGET).elf: $(OFILES)
	@$(CXX) $(LDFLAGS) $(OFILES) $(LIBPATHS) $(LIBS) -o $@

#---------------------------------------------------------------------------------
# Compile source files
#---------------------------------------------------------------------------------
$(BUILD)/%.o: $(SOURCES)/%.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD)/%.o: $(SOURCES)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

#---------------------------------------------------------------------------------
# Include dependency files
#---------------------------------------------------------------------------------
-include $(OFILES:.o=.d)
