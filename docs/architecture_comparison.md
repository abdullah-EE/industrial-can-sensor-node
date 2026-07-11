# Architecture Comparison

## Version 1 Requirement

The first version must be simple, low-cost, understandable, and testable. It should target a 12 V brushed DC motor with roughly 1 A to 2 A maximum intended current and safe shutdown behavior. It does not need reverse direction, closed-loop speed control, BLDC control, FOC, cloud logging, or a dashboard.

## Option A: STM32 Nucleo Plus Discrete Low-Side MOSFET

Summary: Use a NUCLEO-G0B1RE for firmware, a low-side N-channel MOSFET to switch the motor, a flyback diode, a shunt resistor plus INA180 current-sense amplifier, a voltage divider for the 12 V rail, temperature sensing, an accelerometer header, and a CAN transceiver.

Advantages:

- Best learning value for power electronics basics.
- Easy to simulate in LTspice.
- Easy to probe with an oscilloscope.
- Keeps motor direction one-way, which reduces failure modes.
- Uses the Nucleo board for debug, power-up, and firmware bring-up.
- Maps naturally to a future custom PCB.

Disadvantages:

- Requires careful MOSFET, flyback, grounding, and shunt layout decisions.
- No reverse direction.
- Protection is partly firmware-based, so first testing must use a current-limited supply.

Decision: Recommended for Version 1.

## Option B: STM32 Nucleo Plus Integrated Brushed DC Driver

Summary: Use a brushed DC motor driver IC such as DRV8871, DRV8876, DRV8231A, or similar, with the STM32 providing PWM and fault logic.

Advantages:

- Built-in motor protection can reduce first-hardware risk.
- Fewer external power-stage components.
- Some parts include current regulation or current feedback.
- Good for later comparison against a discrete design.

Disadvantages:

- Less educational for MOSFET switching, flyback paths, and current-loop layout.
- Many driver ICs are H-bridges, which adds bidirectional capability before it is needed.
- Thermal-pad packages can be harder for a beginner to solder and inspect.

Decision: Rejected for Version 1, but kept as a backup if the discrete MOSFET stage becomes too difficult.

## Option C: Full H-Bridge With Discrete MOSFETs

Summary: Use four MOSFETs and a gate-driver strategy to control speed and direction.

Advantages:

- Supports forward and reverse.
- Looks closer to a complete motor controller product.
- Teaches high-side switching, dead time, and shoot-through prevention.

Disadvantages:

- Too much risk for Version 1.
- Requires more complex gate driving and layout.
- Shoot-through can destroy parts quickly.
- Harder to debug without strong test equipment habits.

Decision: Rejected for Version 1. Consider only after one-direction control is measured and documented.

## Option D: Custom STM32 PCB From The Start

Summary: Design the STM32, power supply, CAN, sensors, and motor stage all on one board immediately.

Advantages:

- Strong final portfolio artifact if successful.
- Forces complete schematic and PCB ownership.

Disadvantages:

- High bring-up risk.
- Firmware, MCU power, clocking, debug, motor switching, and CAN all fail together if the board has one mistake.
- Slows learning because every bug may be hardware, firmware, or assembly.

Decision: Rejected for Version 1. Use Nucleo first, then custom PCB later.

## Selected Version 1 Architecture

Use Option A:

NUCLEO-G0B1RE + one-direction low-side MOSFET motor stage + shunt current sensing + supply divider + temperature input + accelerometer header + 3.3 V CAN transceiver.

This is the simplest architecture that still demonstrates embedded systems, electronics, robotics, industrial hardware, power electronics, and hardware-test thinking.
