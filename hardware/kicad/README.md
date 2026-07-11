# KiCad Hardware Notes

The active KiCad project is in `kicad/`.

Version 1 schematic sections:

1. Input protection and motor supply
2. Low-side MOSFET motor switch
3. Shunt current sensing
4. 12 V supply voltage sensing
5. Temperature sensing
6. STM32 Nucleo interface
7. CAN transceiver and connector
8. Accelerometer header
9. Test points and debug labels

Important Version 1 net labels:

- `VIN_12V`
- `VMOTOR_12V`
- `MOTOR_SW`
- `MOTOR_CURRENT_SHUNT_HI`
- `MOTOR_CURRENT_SHUNT_LO`
- `ISENSE_ADC`
- `VSENSE_ADC`
- `TEMP_ADC`
- `PWM_GATE`
- `CAN_TX`
- `CAN_RX`
- `CANH`
- `CANL`
- `VDD_3V3`
- `VDD_5V`
- `PGND`
- `AGND`

Layout reminders for the future PCB:

- Keep the motor current loop short and wide.
- Place the flyback diode and bulk capacitor close to the motor connector and MOSFET loop.
- Use Kelvin-style sense routing from the shunt to the current-sense amplifier.
- Keep ADC filter parts close to the MCU input pins.
- Keep CANH/CANL routed as a pair and avoid long stubs.
- Add test points before layout gets crowded.
