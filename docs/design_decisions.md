# Design Decisions

## DD-001: Use STM32G0B1RE Nucleo For Version 1

Decision: Use NUCLEO-G0B1RE for first firmware and hardware bring-up.

Why:

- It includes an STM32 with FDCAN, ADC, timers, watchdogs, and enough flash/RAM.
- It provides SWD debug and USB without designing a custom MCU circuit first.
- It lowers risk while still using a real STM32 workflow.

Rejected alternatives:

- STM32F103 Blue Pill: cheap and popular, but board quality varies and CAN setup can be messy for beginners.
- Custom STM32 PCB first: impressive if it works, but too many bring-up risks at once.

## DD-002: Use One-Direction Low-Side MOSFET First

Decision: Version 1 controls motor speed in one direction only.

Why:

- It teaches MOSFET switching, flyback, shunt sensing, grounding, PWM, and fault shutdown.
- It avoids H-bridge shoot-through and high-side drive complexity.
- It matches the project rule to avoid unnecessary features.

Rejected alternatives:

- Integrated H-bridge: safer in some ways, but hides the power-stage learning.
- Discrete H-bridge: too much risk for Version 1.

## DD-003: Use Low-Side Shunt Current Sensing

Decision: Use a low-side shunt plus current-sense amplifier.

Why:

- It is simple to understand: current through a resistor creates a small voltage.
- It is easy to simulate.
- It is easy to probe.
- INA180-class devices are common and documented.

Tradeoff:

- The motor return is lifted slightly by the shunt voltage.
- Layout matters because noisy motor current and ADC ground must be handled carefully.

## DD-004: Put CAN In Version 1 But Keep Protocol Small

Decision: Include CAN hardware and a tiny command/status protocol.

Why:

- CAN is valuable for industrial and robotics internships.
- Timeout-to-safe-state is a meaningful embedded safety behavior.
- The protocol can stay small: command duty, enable bit, heartbeat, status, fault flags.

Rejected alternatives:

- USB-only control: easier but less aligned with industrial hardware.
- Cloud or dashboard: unnecessary and distracting.

## DD-005: Use External Or Module Power Rails During Bring-Up

Decision: During Version 1, power the Nucleo from USB and use a current-limited 12 V supply for the motor. Do not design the main buck converter yet.

Why:

- A switching regulator is a project by itself.
- Separating the logic supply from motor supply makes first tests safer.
- A custom PCB can add power conversion after the motor stage is proven.

## DD-006: Treat Vibration As An Interface First

Decision: Add a header for an accelerometer module before designing a custom MEMS sensor layout.

Why:

- It supports future condition monitoring.
- It avoids tiny LGA soldering in the first hardware step.
- It keeps Version 1 focused on motor control and fault handling.

## DD-007: Document Uncertainty

Decision: The design documents must mark assumptions and unknowns.

Why:

- Recruiters and engineers trust honest validation more than polished guesses.
- The motor stall current, thermal limits, ADC noise, and CAN timing should be measured later.
