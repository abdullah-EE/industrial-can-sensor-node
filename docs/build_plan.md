# Build Plan

## Stage 0: Repository Baseline

- Create requirements, architecture, research notes, decision log, build plan, progress log, and BOM.
- Begin LTspice simulations.
- Begin KiCad schematic structure.
- Begin firmware scaffold.

## Stage 1: Bench Prototype Without Motor

- Wire Nucleo, gate driver input, MOSFET gate pulldown, and dummy LED/load.
- Generate PWM at low duty.
- Confirm safe-state disables PWM.
- Confirm ADC channels return sane values using known voltages.

Exit criteria:

- PWM pin toggles at expected frequency.
- Duty command is limited by firmware.
- Fault manager can force duty to zero.

## Stage 2: Current-Limited Motor Test

- Use a small 12 V brushed DC motor.
- Set bench supply current limit below the planned maximum at first.
- Start with low duty limit.
- Probe gate, switch node, shunt voltage, current-sense output, and supply rail.

Exit criteria:

- Motor spins in one direction.
- Current reading is plausible compared with bench supply reading.
- Flyback behavior does not exceed component voltage ratings in measured scope captures.

## Stage 3: Fault Handling

- Test overcurrent threshold with a controlled load condition.
- Test undervoltage by lowering supply voltage.
- Test CAN timeout by stopping command frames.
- Test sensor fault behavior using disconnected or forced ADC inputs.

Exit criteria:

- Every critical fault disables PWM.
- Fault code is reported.
- The test log separates expected behavior from measured behavior.

## Stage 4: CAN Bring-Up

- Connect CAN transceiver and USB-CAN adapter or second node.
- Send command frames.
- Receive status frames.
- Confirm command timeout behavior.

Exit criteria:

- Valid command updates duty setpoint.
- Invalid or missing command leads to safe state.

## Stage 5: Custom PCB Preparation

- Convert prototype circuit into a complete KiCad schematic.
- Review current-loop layout.
- Add test points and connector labels.
- Add optional termination and protection footprints.
- Run ERC and DRC.

Exit criteria:

- Schematic reviewed.
- PCB review checklist completed.
- Fabrication is delayed until simulation and bench prototype issues are resolved.
