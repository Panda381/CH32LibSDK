
##############################################################################
#               Include Makefile 1st stage - prepare MCU type
##############################################################################

MCU=CH32V002x4
#MCU=CH32V003x4
#MCU=CH32V006x8
#MCU=CH32X035x8
#MCU=CH32V103x8
#MCU=CH32L103x8
#MCU=CH32V203x8
#MCU=CH32V208xB
#MCU=CH32V303xC
#MCU=CH32V305xC
#MCU=CH32V307xC
#MCU=CH32V317xC

# Setup device class
DEVCLASS=ch32base

# Flag - do not include boot section
NOBOOT=1

# Input variable:
#  MCU ... target MCU = CH32V002x4, CH32V003x4, CH32V004x6 ...

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
TARGET=Pimitachi

# reduce program size
EXTRA_AFLAGS += -D REDUCE_CRT0_SIZE=1

# Flag - use global data section (pointed by global pointer gp)
GLOBALDATA=1

# Destination directory
TARGETDIR=Toys

##############################################################################
#                             Input files
##############################################################################

# ASM source files
ASRC += src/data_asm.S
ASRC += src/disp_asm.S
ASRC += src/draw_asm.S
ASRC += src/key_asm.S
ASRC += src/mem_asm.S

# C source files
CSRC += src/data.c

CSRC += src/anim.c
CSRC += src/ctrl.c
CSRC += src/disp.c
CSRC += src/draw.c
CSRC += src/graph.c
CSRC += src/init.c
CSRC += src/key.c
CSRC += src/main.c
CSRC += src/mem.c
CSRC += src/repaint.c
CSRC += src/sleep.c
CSRC += src/sound.c
CSRC += src/tick.c

CSRC += img/title.c

CSRC += img/baby_eye.c
CSRC += img/pill.c
CSRC += img/hand.c
CSRC += img/dirt.c

CSRC += img/baby.c
CSRC += img/cat.c
CSRC += img/dog.c
CSRC += img/bunny.c
CSRC += img/hamster.c
CSRC += img/bird.c
CSRC += img/dragon.c

CSRC += img/baby_wink.c
CSRC += img/bird_wink.c
CSRC += img/bunny_wink.c
CSRC += img/cat_wink.c
CSRC += img/dog_wink.c
CSRC += img/dragon_wink.c
CSRC += img/hamster_wink.c

CSRC += img/baby_anim.c
CSRC += img/bird_anim.c
CSRC += img/bunny_anim.c
CSRC += img/cat_anim.c
CSRC += img/dog_anim.c
CSRC += img/dragon_anim.c
CSRC += img/hamster_anim.c

CSRC += img/egg_crack.c
CSRC += img/egg_born.c
CSRC += img/egg.c
CSRC += img/egg_bird.c
CSRC += img/egg_bunny.c
CSRC += img/egg_cat.c
CSRC += img/egg_dog.c
CSRC += img/egg_dragon.c
CSRC += img/egg_hamster.c

CSRC += img/bed.c
CSRC += img/zzz.c

CSRC += img/bed_baby.c
CSRC += img/bed_bird.c
CSRC += img/bed_bunny.c
CSRC += img/bed_cat.c
CSRC += img/bed_dog.c
CSRC += img/bed_dragon.c
CSRC += img/bed_hamster.c

CSRC += img/wakeup_baby.c
CSRC += img/wakeup_bird.c
CSRC += img/wakeup_bunny.c
CSRC += img/wakeup_cat.c
CSRC += img/wakeup_dog.c
CSRC += img/wakeup_dragon.c
CSRC += img/wakeup_hamster.c

CSRC += img/state.c

CSRC += img/state_clean.c
CSRC += img/state_cure.c
CSRC += img/state_food.c
CSRC += img/state_game.c
CSRC += img/state_learn.c
CSRC += img/state_rest.c
CSRC += img/state_info.c
CSRC += img/state_giveup.c

CSRC += img/menu_clean.c
CSRC += img/menu_cure.c
CSRC += img/menu_food.c
CSRC += img/menu_game.c
CSRC += img/menu_learn.c
CSRC += img/menu_rest.c
CSRC += img/menu_info.c
CSRC += img/menu_giveup.c

# C++ source files
SRC +=

##############################################################################
#                  Include build Makefile 2nd stage - Build
##############################################################################

# Makefile includes
include ${CH32_ROOT_PATH}/Makefile2.inc
