# Firmware Scaffold

Target board for Version 1: `NUCLEO-G0B1RE`.

This scaffold separates project logic from STM32 HAL setup:

- `main.c` runs the simple application loop.
- `motor_control.*` clamps duty and forces safe shutdown.
- `adc_processing.*` converts raw ADC counts into engineering units.
- `fault_manager.*` owns fault detection and latching.
- `can_protocol.*` encodes and decodes a tiny command/status protocol.
- `platform.h` defines the hardware functions that the STM32Cube layer must provide later.
- `platform_stub.c` is a buildable placeholder for non-hardware review.

The next firmware task is to create an STM32CubeMX project for the NUCLEO-G0B1RE and implement `platform.h` using TIM PWM, ADC DMA or polling, FDCAN, GPIO, and watchdog setup.
