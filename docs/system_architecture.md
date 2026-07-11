# System Architecture

## Version 1 Block Diagram

```text
12 V bench supply
    |
    |-- fuse or resettable fuse
    |-- reverse-polarity protection placeholder
    |-- TVS footprint placeholder
    |-- bulk capacitor
    |
    +--> motor +
          motor -
              |
              +--> low-side N-MOSFET drain
                       source --> shunt resistor --> power ground

STM32 NUCLEO-G0B1RE
    |
    |-- timer PWM --> gate driver or gate resistor --> MOSFET gate
    |-- ADC current input <-- INA180 output <-- shunt resistor
    |-- ADC voltage input <-- divider from protected 12 V
    |-- ADC temperature input <-- NTC or analog temperature sensor
    |-- I2C/SPI header --> vibration accelerometer module
    |-- FDCAN TX/RX --> 3.3 V CAN transceiver --> CANH/CANL connector
    |-- SWD/USB debug through Nucleo
```

## Power Domains

- `VIN_12V`: raw 12 V input from the current-limited bench supply.
- `VMOTOR_12V`: protected motor supply after fuse/protection.
- `VDD_5V`: optional 5 V rail from USB/Nucleo or module for the gate driver during early bring-up.
- `VDD_3V3`: STM32 logic and CAN transceiver supply from the Nucleo board during Version 1.
- `PGND`: high-current motor return.
- `AGND`: analog measurement reference. In Version 1 this joins ground at a planned point near the shunt/ADC reference path.

## Motor Power Stage

The first motor stage is a low-side switch:

- The motor connects between `VMOTOR_12V` and the MOSFET drain.
- The MOSFET source returns through the shunt resistor to ground.
- A flyback diode connects from the MOSFET drain/switch node back to `VMOTOR_12V`.
- A gate pulldown keeps the MOSFET off during reset.
- A series gate resistor reduces ringing and limits gate-drive current.

Beginner explanation: the STM32 cannot power the motor directly. The MOSFET acts like an electronically controlled switch. PWM turns the switch on and off quickly, and the motor averages that into a controllable speed.

## Sensing

Current:

- Use a low-side shunt so the first design is easy to understand.
- Start with 0.05 ohm and INA180A1 gain of 20 V/V.
- At 2 A, the shunt voltage is 0.1 V and the amplifier output is about 2.0 V.
- Shunt power at 2 A is I^2R = 0.2 W, so use a resistor with margin.

Voltage:

- Divide the 12 V rail to fit below the STM32 ADC limit.
- Example ratio: 100 k top and 27 k bottom gives about 2.55 V at 12 V and about 3.19 V at 15 V.
- Add an RC filter close to the MCU ADC pin.

Temperature:

- Start with an NTC divider or analog sensor placed near the MOSFET and motor connector.
- Use conservative firmware thresholds until measured thermal data exists.

Vibration:

- Add a header for an LIS3DH-class module.
- Do not claim condition-monitoring results until real vibration data is captured.

## CAN

- Use the STM32 FDCAN peripheral with a 3.3 V transceiver such as TCAN332.
- Add optional 120 ohm termination using a jumper or solder bridge.
- Keep the CAN stub short.
- Add test points for CANH and CANL.

## Safe State

The safe state is:

- PWM duty forced to 0 percent.
- MOSFET gate driven low or left pulled low.
- Fault latched in firmware until reset or explicit clear, depending on fault type.
- Status frame reports the fault code.
