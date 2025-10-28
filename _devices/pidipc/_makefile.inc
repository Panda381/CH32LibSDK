
# ASM source files
ifneq (${NOBOOT},1)
ASRC += ${CH32LIBSDK_LOADER_DIR}/loader_PidiPC.S
endif
ASRC += ${CH32LIBSDK_DEVICES_DIR}/pidipc/pidipc_vga_asm.S

# C source files
ifeq (${OS},Windows_NT)
CSRC += ${CH32LIBSDK_DEVICES_DIR}/pidipc/pidipc.c
else
CSRC += ${CH32LIBSDK_DEVICES_DIR}/pidipc/pidipc_vga.c
CSRC += ${CH32LIBSDK_DEVICES_DIR}/pidipc/pidipc_draw.c
CSRC += ${CH32LIBSDK_DEVICES_DIR}/pidipc/pidipc_key.c
CSRC += ${CH32LIBSDK_DEVICES_DIR}/pidipc/pidipc_snd.c
CSRC += ${CH32LIBSDK_DEVICES_DIR}/pidipc/pidipc_init.c
endif

DEFINE += -D USE_PIDIPC=1

MCU=CH32V006x8
