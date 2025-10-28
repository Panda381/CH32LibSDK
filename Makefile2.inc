
##############################################################################
#                     Makefile 2nd stage - Build
##############################################################################

# Setup from main Makefile:
#   TARGET ... project name
#   TARGETDIR ... destination directory
#   MCU ... target MCU -> MCU serie, MCU class, MCU subclass:
#	CH32V002x4 -> CH32V002, CH32V0, CH32V00X
#	CH32V003x4 -> CH32V003, CH32V0
#	CH32V004x6 -> CH32V004, CH32V0, CH32V00X
#	CH32V005x6 -> CH32V005, CH32V0, CH32V00X
#	CH32V006x4 -> CH32V006, CH32V0, CH32V00X
#	CH32V006x8 -> CH32V006, CH32V0, CH32V00X
#	CH32V007x8 -> CH32V007, CH32V0, CH32V00X
#	CH32X033x8 -> CH32V033, CH32V0, CH32V03X
#	CH32X035x7 -> CH32V035, CH32V0, CH32V03X
#	CH32X035x8 -> CH32V035, CH32V0, CH32V03X
#	CH32V103x6 -> CH32V103, CH32V1
#	CH32V103x8 -> CH32V103, CH32V1
#	CH32L103x8 -> CH32L103, CH32V1
#	CH32V203x6 -> CH32V203, CH32V2
#	CH32V203x8 -> CH32V203, CH32V2
#	CH32V208xB -> CH32V208, CH32V2
#	CH32V303xB -> CH32V303, CH32V3
#	CH32V303xC -> CH32V303, CH32V3
#	CH32V305xB -> CH32V305, CH32V3
#	CH32V305xC -> CH32V305, CH32V3
#	CH32V307xC -> CH32V307, CH32V3
#	CH32V317xC -> CH32V317, CH32V3

#   MCUCLASS
#	CH32V0
#	CH32V1
#	CH32V2
#	CH32V3

#   CH32V0 MCU subclass
#	CH32V003
#	CH32V00X
#	CH32V03X

##############################################################################

# Path to root directory from the project directory (without trailing '/' delimiter)
# ifeq ($(CH32_ROOT_PATH),)
# CH32_ROOT_PATH = ../../..
# endif

# Path to _font directory (without trailing '/' delimiter)
ifeq ($(CH32LIBSDK_FONT_DIR),)
CH32LIBSDK_FONT_DIR = ${CH32_ROOT_PATH}/_font
endif

# Path to _lib directory (without trailing '/' delimiter)
ifeq ($(CH32LIBSDK_LIB_DIR),)
CH32LIBSDK_LIB_DIR = ${CH32_ROOT_PATH}/_lib
endif

# Path to _sdk directory (without trailing '/' delimiter)
ifeq ($(CH32LIBSDK_SDK_DIR),)
CH32LIBSDK_SDK_DIR = ${CH32_ROOT_PATH}/_sdk
endif

# Path to _loader directory (without trailing '/' delimiter)
ifeq ($(CH32LIBSDK_LOADER_DIR),)
CH32LIBSDK_LOADER_DIR = ${CH32_ROOT_PATH}/_loader
endif

# Path to _tools directory (without trailing '/' delimiter)
ifeq ($(CH32LIBSDK_TOOLS_DIR),)
CH32LIBSDK_TOOLS_DIR = ${CH32_ROOT_PATH}/_tools
endif

# Path to OpenOCD (without trailing '/' delimiter)
ifeq ($(CH32LIBSDK_OPENOCD_DIR),)
CH32LIBSDK_OPENOCD_DIR = ${CH32LIBSDK_TOOLS_DIR}/openocd
endif

##############################################################################
# Input files

# Do not include stdio.h file
DEFINE += -D _STDIO_H_

# SDK
include ${CH32LIBSDK_SDK_DIR}/_makefile.inc

# Libraries
include ${CH32LIBSDK_LIB_DIR}/_makefile.inc

# fonts
include ${CH32LIBSDK_FONT_DIR}/_makefile.inc

# C code define include base "includes.h" file
DEFINE += -D INCLUDES_H=\"${CH32_ROOT_PATH}/includes.h\"

# Includes
IPATH += -I. -I${PICOLIBSDK_SDK_DIR}/

##############################################################################
# Configuration

# temporary build directory
TEMP = ./build

# Base makefile (to ensure recompilation after change)
MAKEFILE = ./Makefile

# Base include file (to ensure recompilation after change)
INCLUDEFILE = ./include.h

# Linker script
ifeq (${GLOBALDATA},1)
LDSCRIPT = ${CH32_ROOT_PATH}/memmap_global.ld
else
LDSCRIPT = ${CH32_ROOT_PATH}/memmap.ld
endif

##############################################################################
# Passing configuration parameters to the source code

# MCU
DEFINE += -D ${MCU}=1

# MCU serie
DEFINE += -D ${MCUSERIE}=1

# MCU class
DEFINE += -D ${MCUCLASS}=1

# SDK subdir
DEFINE += -D SDK_SUBDIR=${SDK_SUBDIR}

# MCU serie extra
ifeq ($(MCUCLASS),CH32V0)
ifneq ($(MCUSERIE),CH32V003)
ifneq ($(MCUSERIE),CH32V033)
ifneq ($(MCUSERIE),CH32V035)
DEFINE += -D CH32V00X=1
endif
endif
endif
endif

ifeq ($(MCUSERIE),CH32V033)
DEFINE += -D CH32V03X=1
endif

ifeq ($(MCUSERIE),CH32V035)
DEFINE += -D CH32V03X=1
endif

# Flash size
DEFINE += -D FLASHSIZE=${FLASHSIZE}

# SRAM size
DEFINE += -D RAMSIZE=${RAMSIZE}

# Stack size
DEFINE += -D STACKSIZE=${STACKSIZE}

##############################################################################
# Architecture setup

# RISC-V instruction set (QingKeV2 processor with RV32EC instruction set)
# - standard RV32EC instrucion extensions: half-word and byte operation compression instructions
# - XW extensions
# - hardware prologie/epilogue HPE (2 levels)
# - vector table free VTF
# - streamlined singe-wire serial debug interface SDI
# - WFI and WFE sleep instructions

ifeq ($(MCUSERIE),CH32V003)
ARCHCFG += -march=rv32ecxw -mabi=ilp32e
else
ifeq ($(MCUSERIE),CH32V033)
ARCHCFG += -march=rv32imacxw -mabi=ilp32
else
ifeq ($(MCUSERIE),CH32V035)
ARCHCFG += -march=rv32imacxw -mabi=ilp32
else
ifeq ($(MCUCLASS),CH32V0)
ARCHCFG += -march=rv32ec_zmmul_xw -mabi=ilp32e
else
ARCHCFG += -march=rv32imacxw -mabi=ilp32
endif
endif
endif
endif

##############################################################################
# Linker setup

# Architecture
LDFLAGS += $(ARCHCFG)

# No built-in functions (This is case when compiller changes printf("x") to putchar('x'))
LDFLAGS += -Wl,--build-id=none

# Link with libnosys.a (libc without system functions)
LDFLAGS += --specs=nano.specs

# Generate map file
LDFLAGS += -Wl,-Map=$(TARGET).map

# Use this link script
LDFLAGS += -Wl,-script=$(LDSCRIPT)
#LDFLAGS += -T $(LDSCRIPT)

# Eliminate unused sections
LDFLAGS += -Wl,--gc-sections

# No start files
LDFLAGS += -nostartfiles

# Extra user's linker flags
LDFLAGS += ${EXTRA_LDFLAGS}

# Pass memory size to the linker script
LDFLAGS += -Wl,--defsym=__FLASH_SIZE__=${FLASHSIZE}
LDFLAGS += -Wl,--defsym=__RAM_SIZE__=${RAMSIZE}
LDFLAGS += -Wl,--defsym=__STACK_SIZE__=${STACKSIZE}

##############################################################################
# Common compiler setup

# Output dependency rule
ARCHCFG += -MMD

# Add phony target for each dependency
ARCHCFG += -MP

# Dependency file
ARCHCFG += -MF"$(@:%.o=%.d)"

# Target dependency generation
ARCHCFG += -MT"$(@)"

##############################################################################
# ASM setup

# Common compiler setup
AFLAGS += $(ARCHCFG)

# Default language is assembler
AFLAGS += -x assembler-with-cpp

# Extra user's ASM flags
AFLAGS += ${EXTRA_AFLAGS}

##############################################################################
# C setup

# Common compiler setup
CFLAGS += $(ARCHCFG)

# Optimization level
#CFLAGS += -O0	# do no optimization
#CFLAGS += -O1	# optimize minimally
#CFLAGS += -O2	# optimize more
#CFLAGS += -O3	# optimize even more
#CFLAGS += -Ofast # optimize for speed
#CFLAGS += -Og -g3 # optimize for debugger (use together with -g0..-g3, level of debugging information)
CFLAGS += -Os	# optimize for size

# Generate uninitialized global variable (to check multiple declarations)
CCFLAGS += -fno-common

# Warn if variable is not initialized
CFLAGS += -Wuninitialized

# Put global and static data smaller than 'n' bytes into a special section 
CFLAGS += -msmall-data-limit=0

# Create separate sections (to enable eliminate unused sections)
CFLAGS += -ffunction-sections -fdata-sections 

# Use unsigned char (this is default for ARM cpu)
CFLAGS += -funsigned-char

# Report if function does not return value
CFLAGS += -Wreturn-type

# Generate debug informations
#CFLAGS += -g3

# Warning as errors
CFLAGS += -Werror

# Extra user's C flags
CFLAGS += ${EXTRA_CFLAGS}

##############################################################################
# C++ setup

# Common compiler setup
CPPFLAGS += $(CFLAGS)

# Do not use exceptions and unwind frames
CPPFLAGS += -fno-exceptions -fno-unwind-tables
CPPFLAGS += -fno-rtti -fno-use-cxa-atexit -std=gnu++17

# Extra user's C++ flags
CPPFLAGS += ${EXTRA_CPPFLAGS}

##############################################################################
# Compiler tools

# Compiler base
COMP = riscv-none-elf-

# C compiler name
CC = ${COMP}gcc

# C++ compiler name
CPP = ${COMP}g++

# ASM compiler name
AS = ${COMP}gcc

# Linker
LD = ${COMP}g++

# Object dump
OD = ${COMP}objdump

# Object copy
OC = ${COMP}objcopy

# Names
NM = ${COMP}nm

# Size
SZ = ${COMP}size

##############################################################################
# File list

# List of all source files
ALLSRC = $(ASRC) $(CSRC) $(SRC)

# List of all files without directory and without extension
ALLBASE = $(notdir $(basename $(ALLSRC)))

# List of all object files *.o
ALLOBJ = $(addprefix $(TEMP)/, $(addsuffix .o, $(ALLBASE)))

##############################################################################
# Clear temporary directory (use "make clean")

clean:
	@${CH32LIBSDK_TOOLS_DIR}/rm -rf $(TEMP)
ifeq (${DEVCLASS},tweetyboy)
	@${CH32LIBSDK_TOOLS_DIR}/rm -f ./$(TARGET).hex ./$(TARGET).lst ./$(TARGET).map ./$(TARGET).sym ./$(TARGET).siz
else
ifeq (${DEVCLASS},pidiboy)
	@${CH32LIBSDK_TOOLS_DIR}/rm -f ./$(TARGET).hex ./$(TARGET).lst ./$(TARGET).map ./$(TARGET).sym ./$(TARGET).siz
else
ifeq (${DEVCLASS},pidipc)
	@${CH32LIBSDK_TOOLS_DIR}/rm -f ./$(TARGET).hex ./$(TARGET).lst ./$(TARGET).map ./$(TARGET).sym ./$(TARGET).siz
else
ifeq (${DEVCLASS},pidipad)
	@${CH32LIBSDK_TOOLS_DIR}/rm -f ./$(TARGET).hex ./$(TARGET).lst ./$(TARGET).map ./$(TARGET).sym ./$(TARGET).siz
else
	@${CH32LIBSDK_TOOLS_DIR}/rm -f ./$(TARGET).lst ./$(TARGET).map ./$(TARGET).sym ./$(TARGET).siz
endif
endif
endif
endif
# ./$(TARGET).elf ./$(TARGET).bin

##############################################################################
# Compile all (use "make all")

all: createdirs elf bin hex lst sym siz

##############################################################################
# Create temporary directory

createdirs:
ifeq (${OS},Windows_NT)
	@${CH32LIBSDK_TOOLS_DIR}/mkdir.exe -p $(TEMP)
else
	@mkdir -p $(TEMP)
endif
	@echo MCU: ${MCU}, Target: ${TARGET}

##############################################################################
# Dependencies of output files

elf: ./$(TARGET).elf
bin: ./$(TARGET).bin
hex: ./$(TARGET).hex
lst: ./$(TARGET).lst
sym: ./$(TARGET).sym
siz: ./$(TARGET).siz

##############################################################################
# Create .bin file from .elf file

./$(TARGET).bin: ./$(TARGET).elf
	@echo     bin		 $@
	@$(OC) -O binary $< $@
ifeq (${DEVCLASS},pidipc)
ifneq (${NOBOOT},1)
	@echo     crc		 $@
	@${CH32LIBSDK_LOADER_DIR}/PidiPC/loadercrc/LoaderCrc $@ $(TARGET).elf
endif
endif
ifeq (${DEVCLASS},pidipad)
ifneq (${NOBOOT},1)
	@echo     crc		 $@
	@${CH32LIBSDK_LOADER_DIR}/PidiPad/loadercrc/LoaderCrc $@ $(TARGET).elf
endif
endif
ifeq (${DEVCLASS},pidiboy)
ifneq (${NOBOOT},1)
	@echo     crc		 $@
	@${CH32LIBSDK_LOADER_DIR}/PidiBoy/loadercrc/LoaderCrc $@ $(TARGET).elf
endif
endif
ifeq (${DEVCLASS},tweetyboy)
ifneq (${NOBOOT},1)
	@echo     crc		 $@
	@${CH32LIBSDK_LOADER_DIR}/TweetyBoy/loadercrc/LoaderCrc $@ $(TARGET).elf
endif
endif

##############################################################################
# Create .hex file from .elf file

./$(TARGET).hex: ./$(TARGET).elf
	@echo     hex		 $@
	@$(OC) -O ihex $< $@

##############################################################################
# Create .lst file from .elf file

./$(TARGET).lst: ./$(TARGET).elf
	@echo     lst		 $@
	@$(OD) --all-headers -M xw -d -S $< > $@

##############################################################################
# Create .sym file from .elf file

./$(TARGET).sym: ./$(TARGET).elf
	@echo     sym		 $@
	@$(NM) -n $< > $@

##############################################################################
# Create .siz file from .elf file

./$(TARGET).siz: ./$(TARGET).elf
	@echo     siz		 $@
	@$(SZ) $< > $@
	@echo.
	@type $@

##############################################################################
# Create .o files from .c files

define CC_TEMP
$(TEMP)/$(notdir $(basename $(1))).o : $(1) $(MAKEFILE) $(INCLUDEFILE)
	@echo     CC		 $$<
	@$(CC) $$(DEFINE) $$(IPATH) $$(CFLAGS) -std=gnu11 -c $$< -o $$@
endef

$(foreach src, $(CSRC), $(eval $(call CC_TEMP, $(src))))

##############################################################################
# Create .o files from .cpp files

define CPP_TEMP
$(TEMP)/$(notdir $(basename $(1))).o : $(1) $(MAKEFILE) $(INCLUDEFILE)
	@echo     C++		 $$<
	@$(CPP) $$(DEFINE) $$(IPATH) $$(CPPFLAGS) -c $$< -o $$@
endef

$(foreach src, $(SRC), $(eval $(call CPP_TEMP, $(src))))

##############################################################################
# Create .o files from .S files

define AS_TEMP
$(TEMP)/$(notdir $(basename $(1))).o : $(1) $(MAKEFILE) $(INCLUDEFILE)
	@echo     ASM		 $$<
	@$(CC) $$(DEFINE) $$(IPATH) $$(AFLAGS) -c $$< -o $$@
endef

$(foreach src, $(ASRC), $(eval $(call AS_TEMP, $(src))))

##############################################################################
# Create .elf from .o files

./$(TARGET).elf: $(ALLOBJ) $(MAKEFILE) $(LDSCRIPT)
	@echo     ld		 $@
	@$(LD) $(LDFLAGS) $(ALLOBJ) -o $@

##############################################################################
# Head dependencies, to recompile C after changing H

ifneq (${MAKECMDGOALS},clean)
-include $(wildcard $(TEMP)/*.d)
endif

##############################################################################
# List of dependencies not creating files

.PHONY: clean all createdirs elf bin hex lst sym siz uf2

##############################################################################
# Erase device flash

erase:
	$(CH32LIBSDK_OPENOCD_DIR)/openocd -f $(CH32LIBSDK_OPENOCD_DIR)/wch-riscv.cfg -c init -c halt -c "flash erase_sector wch_riscv 0 last" -c exit

##############################################################################
# Write device flash

flash:
	$(CH32LIBSDK_OPENOCD_DIR)/openocd -f $(CH32LIBSDK_OPENOCD_DIR)/wch-riscv.cfg -c init -c halt -c "flash erase_sector wch_riscv 0 last " -c "program ./$(TARGET).elf" -c "verify_image ./$(TARGET).elf" -c reset -c resume -c exit

##############################################################################
# Reset device

reset:
	$(CH32LIBSDK_OPENOCD_DIR)/openocd -f $(CH32LIBSDK_OPENOCD_DIR)/wch-riscv.cfg -c init -c reset -c resume -c exit
