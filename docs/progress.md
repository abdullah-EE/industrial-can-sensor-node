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

## 2026-07-12 Version 1 Electrical Selection Pass

### Completed

- Selected the Version 1 motor: Pololu item 3039, 50:1 Micro Metal Gearmotor HPCB 12V.
- Used manufacturer data for the motor selection:
  - 12 V rated voltage
  - 80 mA no-load current
  - 0.75 A extrapolated stall current
- Finalized exact critical parts in `hardware/bom.csv`:
  - Infineon IRLZ44NPBF MOSFET
  - Microchip TC4427ACPA MOSFET driver
  - Diodes Incorporated 1N5822 flyback diode
  - Bourns CSS2H-2512R-L500F 0.05 ohm shunt
  - Littelfuse RXEF110 resettable PTC
  - Littelfuse SMBJ18A TVS diode
  - Texas Instruments INA180A1IDBVR current-sense amplifier
  - Texas Instruments TCAN332DR CAN transceiver
- Added `docs/design_calculations.md` with current, voltage, power, thermal, ADC-scaling, divider, shunt, MOSFET, diode, fuse, and TVS calculations.
- Updated firmware current thresholds to match the selected small motor:
  - stall detection current: 0.75 A
  - overcurrent shutdown: 1.20 A
- Updated LTspice motor model resistance to 16 ohm from the selected motor's 12 V / 0.75 A stall estimate.
- Replaced the KiCad text-only roadmap with a first real-symbol schematic pass using KiCad symbols for the MOSFET, diode, gate driver, INA180, TCAN332, connectors, protection, sensing, and passives.
- Confirmed the new KiCad schematic loads and exports a netlist.
- Ran KiCad ERC and saved the actual report to `hardware/kicad/erc_2026-07-12.rpt`.

### Blockers And Uncertainties

- LTspice was not installed on PATH or under the usual Program Files locations, so no actual LTspice plots or exported waveform data were generated.
- KiCad ERC is not clean. The current report has 63 errors and 102 warnings, mostly from dangling labels and off-grid hand-written wire endpoints.
- The KiCad schematic is a real-symbol first pass, but it still needs a KiCad GUI cleanup pass before it can be called electrically complete.
- Some exact footprints need verification or library mapping before PCB layout.
- The selected motor's stall current is manufacturer-extrapolated, not measured on the purchased motor.

### Blockers And Uncertainties

- Motor stall current must still be measured on the exact purchased motor before final lab validation.
- Temperature sensor conversion is a firmware placeholder until the exact NTC or analog sensor is selected.
- The KiCad schematic currently contains real symbols but is not ERC-clean.
- No local C compiler or CMake was available on PATH, so the firmware scaffold was not compiled in this environment.
- LTspice files were updated but not simulated here because LTspice was not installed.

### Next Task

Fix KiCad schematic placement and ERC issues before routing:

- snap all symbols, wires, and labels to KiCad's connection grid
- fix all dangling labels and multiple-net-name warnings
- verify/import exact footprints for terminal blocks, PTC, thermistor, and test points
- rerun ERC until no genuine errors remain
- run LTspice on a machine with LTspice installed and save real waveform data
