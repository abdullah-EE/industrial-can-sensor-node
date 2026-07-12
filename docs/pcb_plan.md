# PCB Plan

## Scope

This is PCB preparation only. The board has a two-layer outline and logical component placement, but no traces are routed yet.

## Footprint And Pin Checks

Critical pin numbering was checked against manufacturer datasheets:

- IRLZ44NPBF: TO-220AB pin 1 gate, pin 2 drain, pin 3 source, tab drain. The schematic now maps Q1 pin 1 to `PWM_GATE`, pin 2 to `MOTOR_SW`, and pin 3 to `MOTOR_CURRENT_SHUNT_HI`.
- TC4427ACPA: PDIP-8 footprint. Pin 2 is IN A, pin 3 is GND, pin 4 is IN B, pin 5 is OUT B, pin 6 is VDD, pin 7 is OUT A. Unused input B is grounded.
- INA180A1IDBVR: SOT-23-5 DBV pinout A. Pin 1 OUT, pin 2 GND, pin 3 IN+, pin 4 IN-, pin 5 VS.
- TCAN332DR: SOIC-8. Pin 1 TXD, pin 2 GND, pin 3 VCC, pin 4 RXD, pin 5 NC, pin 6 CANL, pin 7 CANH, pin 8 NC.
- 1N5822: DO-201AD axial Schottky diode, cathode-band side connected to `VMOTOR_12V` for the flyback path.
- SMBJ18A: DO-214AA / SMB unidirectional TVS. Cathode side is planned on `VMOTOR_12V`, anode side on `PGND`.
- RXEF110: radial resettable PTC footprint added as a project footprint using the RXEF110 body and lead data.

Project-specific footprints were added for exact/selected parts not available as stock KiCad footprints:

- `Project_Footprints:Littelfuse_RXEF110`
- `Project_Footprints:OnShore_OSTVN02A150`
- `Project_Footprints:OnShore_OSTVN03A150`

## Board Outline And Placement

The board outline is a simple 120 mm x 80 mm two-layer rectangle.

Placement intent:

- 12 V input connector, PTC, TVS, and bulk capacitor sit together near the upper-left input area.
- Motor connector, flyback diode, MOSFET, and shunt are grouped in the left/middle motor-current area.
- TC4427 gate driver is close to the MOSFET gate resistor and gate pulldown.
- INA180 is close to the shunt, with the layout marked for Kelvin-style sense routing.
- TCAN332 is close to the CAN connector and CAN termination resistor.
- C4, C6, and C7 are local 100 nF decoupling capacitors near the TC4427, INA180, and TCAN332 supply pins.
- Test points are arranged along the lower board edge for easier probing.
- Four M3 mounting holes were placed near the corners.

## Ground And Current-Loop Strategy

The noisy current path is:

`VMOTOR_12V -> motor connector -> motor -> MOTOR_SW -> MOSFET drain/source -> shunt -> PGND -> input return`

During routing, this loop should be short and wide. The motor loop should stay on the left/motor side of the board. Analog signals and MCU/CAN logic should stay to the right where possible.

The shunt needs Kelvin-style sensing: the INA180 input traces should come from the shunt pads as separate thin sense traces, not from the wide motor-current copper after current has already spread through the board. This makes the current reading depend mostly on the shunt resistor voltage, not random copper voltage drops.

Use a bottom-layer ground pour later, but do not let high motor current force its way through the quiet analog/MCU area. The quiet sensing ground should return near the shunt/input-return area deliberately.

## Trace-Width Plan

No traces are routed yet. Planned starting widths:

- Motor and 12 V supply current paths: 1.0 mm minimum, preferably 1.5 mm to 2.0 mm where space allows.
- Shunt-to-MOSFET and motor flyback loop: short, wide copper with minimal loop area.
- Gate drive: about 0.25 mm to 0.40 mm is fine, kept short between TC4427, gate resistor, and MOSFET gate.
- ADC and INA180 sense traces: about 0.20 mm to 0.25 mm, routed as quiet Kelvin/signal traces away from the motor switch node.
- CANH/CANL: about 0.25 mm to 0.40 mm, routed together and kept away from the MOSFET switch node.

These are conservative beginner-friendly choices for a low-current 12 V board. Final widths should still be checked with the board house copper weight and temperature-rise assumptions before ordering.

## Current Check Results

KiCad checks run:

- Schematic ERC: `0 Errors, 0 Warnings`
- PCB DRC physical placement: `0 DRC violations`
- PCB unconnected items: `60`, expected because routing has not started
- Schematic parity warnings: `8`
  - 4 missing `PWR_FLAG` footprints, expected because schematic power flags are not physical PCB parts
  - 4 extra mounting-hole footprints, expected because mounting holes were intentionally added to the PCB

PCB routing has not started.

## Sources Used

- Infineon IRLZ44N datasheet
- Microchip TC4426A/TC4427A/TC4428A datasheet
- Texas Instruments INA180 datasheet
- Texas Instruments TCAN33x datasheet
- Diodes Incorporated 1N5822 datasheet
- Littelfuse SMBJ series datasheet
- Littelfuse RXEF series datasheet
- On Shore Technology OSTVNxxA150 drawing
