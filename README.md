# FreeRTOS RISC-V Demo

This is a FreeRTOS demonstration project for RISC-V (RV32) running on QEMU virtual machine.

## Features
- Mutex task implementation
- Deadlock task demonstration
- RISC-V virtual machine support

## Build Instructions
```bash
cd build/gcc
make
```

## Run
```bash
qemu-system-riscv32 -machine virt -bios none -kernel output/RTOSDemo.elf -nographic
```

## Project Structure
- `main.c` - Main application entry point
- `mutex_task.c` - Mutex demonstration tasks
- `deadlock_task.c` - Deadlock scenario tasks
- `FreeRTOSConfig.h` - FreeRTOS configuration
