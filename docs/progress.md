# Progress Log

## 2026-07-12

### Completed

- Inspected the repository and found an early 24 V industrial sensor-node skeleton with empty KiCad files and LTspice placeholders.
- Redirected the project to a 12 V smart brushed-DC motor controller and condition-monitoring node.
- Researched primary manufacturer and tool documentation for STM32G0B1RE, NUCLEO-G0B1RE, INA180 current sensing, brushed DC driver alternatives, CAN physical layer guidance, TCAN332, TC4427A, LIS3DH, KiCad, and LTspice.
- Reviewed common engineering-community patterns and beginner mistakes for motor-driver, PCB, and portfolio projects.
- Compared four Version 1 architectures.
- Selected the simplest strong Version 1 architecture: NUCLEO-G0B1RE plus one-direction low-side MOSFET motor stage, shunt current sensing, supply-voltage sensing, temperature sensing, accelerometer header, and CAN transceiver.
- Created:
  - `docs/research_notes.md`
  - `docs/architecture_comparison.md`
  - `docs/requirements.md`
  - `docs/system_architecture.md`
  - `docs/design_decisions.md`
  - `docs/build_plan.md`
  - `hardware/bom.csv`
- Began LTspice simulation files:
  - `hardware/ltspice/v1_low_side_motor_switch.cir`
  - `hardware/ltspice/v1_current_sense_filter.cir`
  - `hardware/ltspice/v1_voltage_divider_filter.cir`
- Began the KiCad schematic as a Version 1 schematic roadmap with named sections, nets, and required test points.
- Validated the KiCad schematic can be parsed/exported by KiCad 10 CLI.
- Created the firmware scaffold with modules for ADC conversion, CAN protocol, fault management, motor control, and platform abstraction.
- Updated `.gitignore` for KiCad history and local validation scratch files.

### Blockers And Uncertainties

- Exact 12 V motor part number is not selected yet.
- Motor stall current is unknown and must be measured before final fuse, MOSFET, diode, and shunt choices are locked.
- Exact MOSFET, flyback diode, TVS, and fuse/PTC are still candidates.
- Temperature sensor conversion is a firmware placeholder until the exact NTC or analog sensor is selected.
- The KiCad schematic currently contains a structured roadmap, not final placed electrical symbols.
- No local C compiler or CMake was available on PATH, so the firmware scaffold was not compiled in this environment.
- LTspice files were created but not simulated here.

### Next Task

Choose the exact small 12 V brushed DC motor and one candidate MOSFET/flyback diode pair, then replace the KiCad roadmap blocks with real schematic symbols for:

- motor connector and input protection
- MOSFET switch and flyback diode
- shunt plus INA180 current-sense amplifier
- voltage divider and ADC filters
- Nucleo header interface
- CAN transceiver and termination option
- test points
