# Requirements

## Scope

Version 1 is a bench-tested 12 V brushed DC motor controller and condition-monitoring node.

## Functional Requirements

| ID | Requirement | Version 1 Target |
|---|---|---|
| F-001 | Motor control | One-direction PWM control of a small brushed DC motor |
| F-002 | PWM frequency | Start at 20 kHz unless switching losses or measurement noise require adjustment |
| F-003 | Motor voltage | Nominal 12 V DC |
| F-004 | Motor current | Selected motor is 80 mA no-load and 0.75 A extrapolated stall; Version 1 overcurrent target is 0.90 A for 10 ms and sustained-stall target is 0.60 A for 150 ms |
| F-005 | Current measurement | Low-side shunt and current-sense amplifier into STM32 ADC |
| F-006 | Supply measurement | Resistor divider and RC filter into STM32 ADC |
| F-007 | Temperature measurement | NTC or simple analog temperature sensor near MOSFET/motor connector |
| F-008 | Vibration interface | Header for a digital accelerometer module, initially LIS3DH-class I2C/SPI |
| F-009 | CAN communication | Receive command, transmit status, detect command timeout |
| F-010 | Safe shutdown | Force PWM duty to zero on critical faults |

## Fault Requirements

| ID | Fault | Version 1 Behavior |
|---|---|---|
| FAULT-001 | Overcurrent | Disable PWM if filtered current exceeds limit |
| FAULT-002 | Stall | Disable or limit PWM if high current persists while command is nonzero |
| FAULT-003 | Overtemperature | Disable PWM above configured temperature threshold |
| FAULT-004 | Undervoltage | Disable PWM below configured 12 V rail threshold |
| FAULT-005 | Sensor failure | Disable PWM if ADC reading is impossible or stuck out of range |
| FAULT-006 | CAN timeout | Disable PWM if no valid command arrives within timeout |

## Safety And Test Requirements

- First power-up must use a current-limited supply.
- First motor tests should begin with a low duty limit, such as 10 percent.
- The motor stage must include a flyback path.
- The motor supply must include bulk capacitance near the motor connector.
- Current shunt power must be checked before hardware testing.
- Test points are required for 12 V input, protected motor supply, gate drive, switch node, shunt sense, current-sense output, 3.3 V, CANH, CANL, and ground.
- Simulation results must be labeled as simulation only.
- Measured results must include test setup notes.

## Non-Goals For Version 1

- Bidirectional motor control
- BLDC control
- Field-oriented control
- Cloud connection
- Mobile or web dashboard
- Machine-learning fault detection
- High-power motor operation
- Automotive qualification
- Functional safety certification

## Open Uncertainties

- Measured stall current for the exact purchased Pololu 3039 motor.
- Real startup current waveform at the selected PWM frequency.
- Whether the first CAN transceiver will be a breakout module or on a small custom board.
- Exact accelerometer module choice.
- Final ADC sampling rate and filter constants after noise measurements.
