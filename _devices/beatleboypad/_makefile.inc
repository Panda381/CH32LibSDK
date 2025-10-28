# ASM source files
ASRC += ${CH32LIBSDK_DEVICES_DIR}/beatleboypad/beatleboypad_asm.S

# C source files
ifeq (${OS},Windows_NT)
CSRC += ${CH32LIBSDK_DEVICES_DIR}/beatleboypad/beatleboypad.c
else
CSRC += ${CH32LIBSDK_DEVICES_DIR}/beatleboypad/beatleboypad_disp.c
CSRC += ${CH32LIBSDK_DEVICES_DIR}/beatleboypad/beatleboypad_draw.c
CSRC += ${CH32LIBSDK_DEVICES_DIR}/beatleboypad/beatleboypad_key.c
CSRC += ${CH32LIBSDK_DEVICES_DIR}/beatleboypad/beatleboypad_snd.c
CSRC += ${CH32LIBSDK_DEVICES_DIR}/beatleboypad/beatleboypad_init.c
endif

DEFINE += -D USE_BEATLEBOYPAD=1

#MCU=CH32V002x4
#MCU=CH32V003x4
#MCU=CH32V006x8

# reduce program size
EXTRA_AFLAGS += -D REDUCE_CRT0_SIZE=1
