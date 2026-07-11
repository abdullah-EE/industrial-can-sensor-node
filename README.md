# Industrial CAN Sensor Node

A staged electrical and embedded-systems portfolio project for industrial, robotics, electronics, and hardware internships.

## Goal
Design and later build a protected 24 V industrial sensor node that:

- reads analog and digital sensors,
- communicates over CAN,
- detects power, sensor, and communication faults,
- enters a safe state when necessary,
- records and reports diagnostic information.

## Current phase
**Phase 1: online design and simulation**

The first stage focuses on requirements, component selection, LTspice simulations, KiCad schematic and PCB design, firmware architecture, and a validation plan. Physical assembly and lab testing will come later.

## Repository structure

- `hardware/kicad/` — KiCad schematic and PCB files
- `hardware/ltspice/` — LTspice simulations
- `firmware/` — STM32 firmware
- `docs/` — requirements, architecture, CAN protocol, and design decisions
- `tests/` — fault matrix and validation procedures

## Planned technical scope

- protected 18–30 V DC input
- 24 V to 5 V buck stage
- 5 V to 3.3 V regulation
- STM32 microcontroller
- CAN transceiver
- 0–10 V analog sensor input
- digital sensor input
- watchdog supervision
- safe-state output
- diagnostic fault codes

## Status
This repository is under active development. Simulation is not being presented as physical validation; measured results will be added after the board is fabricated and tested.
