# Smart Brushed DC Motor Controller and Monitor

A staged electrical and embedded-systems portfolio project for industrial, robotics, electronics, power electronics, and hardware-test internships.

## Goal

Design and later build a low-voltage brushed DC motor controller that:

- controls a small 12 V brushed DC motor with PWM
- measures motor current and supply voltage
- monitors temperature and vibration
- detects stall, overcurrent, overheating, undervoltage, sensor failure, and CAN timeout
- shuts the motor down safely during critical faults
- communicates status and commands over CAN
- starts on a dev board and moves toward a custom PCB only after the basics are proven

## Current Version 1 Direction

Version 1 uses an STM32 Nucleo board, a discrete one-direction low-side MOSFET motor switch, shunt current sensing, divided supply-voltage sensing, basic temperature sensing, an accelerometer header, and a CAN transceiver.

This is intentionally not a BLDC, FOC, cloud, AI, dashboard, or high-power motor project.

## Repository Structure

- `docs/` - research notes, requirements, architecture, design decisions, and build plan
- `hardware/bom.csv` - first-pass bill of materials
- `hardware/ltspice/` - simulation starters
- `hardware/kicad/` - KiCad hardware notes
- `kicad/` - KiCad project files
- `firmware/` - STM32 firmware scaffold

## Validation Rule

Simulation results and measured results are separate. Anything in LTspice is design exploration until it is later checked on real hardware with a current-limited supply, meter, oscilloscope, and documented test procedure.
