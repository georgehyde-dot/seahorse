#!/bin/bash
set -xue

# QEMU file path (MACOS specific)
QEMU=/opt/homebrew/bin/qemu-system-riscv32

# path to clang and compiler flags
CC=/opt/homebrew/opt/llvm/bin/clang
CFLAGS="-std=c11 -O2 -g3 -Wall -Wextra --target=riscv32-unknown-elf -fno-stack-protector -ffreestanding -nostdlib"

# build kernel
$CC $CFLAGS -Wl,-Tkernel.ld -Wl,-Map=kernel.map -o kernel.elf \
    kernel.c

#Start QEMU
$QEMU -machine virt -bios default -nographic -serial mon:stdio --no-reboot
    -kernel kernel.elf
