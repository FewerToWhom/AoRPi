ARMGNU ?= arm-none-eabi

BUILD = ../build/

CFLAGS = -c -Wpadded -fno-builtin -mfloat-abi=hard -marm -march=armv6 -fomit-frame-pointer -O2 -std=c99 #-pedantic-errors

ASFLAGS = -mfpu=vfpv2

LDFLAGS = --no-undefined
