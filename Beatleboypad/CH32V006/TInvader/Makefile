
##############################################################################
#               Include Makefile 1st stage - prepare MCU type
##############################################################################

#MCU=CH32V002x4
#MCU=CH32V003x4
MCU=CH32V006x8

# Setup device class
DEVCLASS=beatleboypad

# Path to root directory from the project directory (without trailing '/' delimiter)
CH32_ROOT_PATH = ../../..

# Makefile includes
include ${CH32_ROOT_PATH}/Makefile1.inc

# Derived variables:
#   target MCU -> MCU serie, MCU class:
#	CH32V002x4 -> CH32V002, CH32V0
#	CH32V003x4 -> CH32V003, CH32V0
#	CH32V004x6 -> CH32V004, CH32V0
#	CH32V005x6 -> CH32V005, CH32V0
#	CH32V006x4 -> CH32V006, CH32V0
#	CH32V006x8 -> CH32V006, CH32V0
#	CH32V007x8 -> CH32V007, CH32V0
#	CH32X033x8 -> CH32V033, CH32V0
#	CH32X035x7 -> CH32V035, CH32V0
#	CH32X035x8 -> CH32V035, CH32V0
#	CH32V103x6 -> CH32V103, CH32V1
#	CH32V103x8 -> CH32V103, CH32V1
#	CH32L103x8 -> CH32V103, CH32V1

# MCU=CH32V002x4 ... target MCU
# MCUSERIE=CH32V002 ... MCU serie
# MCUCLASS=CH32V0 ... MCU class
# SDK_SUBDIR=ch32v00x ... SDK subdirectory
# FLASHSIZE=0x4000 ... Flash size in bytes
# RAMSIZE=0x1000 ... RAM size in bytes
# STACKSIZE=512 ... Stack size in bytes

##############################################################################
#                           Project base configuration
##############################################################################

# Target project name
TARGET=TInvader

# Destination directory
TARGETDIR=CH32V006

##############################################################################
#                             Input files
##############################################################################

# ASM source files
ASRC +=

# C source files
CSRC += ../../CH32V002/TInvader/src/main.c
CSRC += ../../CH32V002/TInvader/src/Tiny-invaders.c

# C++ source files
SRC +=

##############################################################################
#                  Include build Makefile 2nd stage - Build
##############################################################################

# Makefile includes
include ${CH32_ROOT_PATH}/Makefile2.inc
