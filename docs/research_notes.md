# Research Notes

## Project Framing

The project was redirected from a generic industrial CAN sensor node into a smart brushed-DC motor controller and condition-monitoring node. That is a stronger portfolio direction because it combines embedded firmware, power switching, sensing, protection, CAN communication, PCB design, and test planning in one buildable system.

The Version 1 design should prove the core behavior first:

- PWM control of a small 12 V brushed DC motor
- motor current measurement
- 12 V supply measurement
- simple temperature measurement
- vibration sensor interface
- CAN communication
- safe shutdown on faults

## Primary Technical Sources Reviewed

- STMicroelectronics STM32G0B1RE product page: the STM32G0B1 family includes a 64 MHz Arm Cortex-M0+ core, up to 512 KB flash, 144 KB SRAM, ADC, timers, comparators, watchdogs, and two FDCAN peripherals. This makes it a practical student MCU for PWM, ADC sampling, fault logic, and CAN without moving to a complex motor-control MCU. Source: https://www.st.com/en/microcontrollers-microprocessors/stm32g0b1re.html
- STMicroelectronics NUCLEO-G0B1RE page: the Nucleo-64 board exposes Arduino and ST morpho headers and includes the STM32G0B1RE MCU. This is useful for first bring-up because it provides SWD debug and USB without requiring a custom MCU board on day one. Source: https://www.st.com/en/evaluation-tools/nucleo-g0b1re.html
- TI INA180 product page and datasheet summary: the INA180 is a low-cost current-sense amplifier that can operate from 2.7 V to 5.5 V, has fixed gain options, and supports low-side current sensing. This fits a simple shunt measurement design. Source: https://www.ti.com/product/INA180
- TI DRV8871 product page and documentation list: integrated brushed DC motor drivers include current regulation and protection, but they hide some of the power-stage learning. The DRV8871 is still a useful rejected-option reference for current ratings, protection, and board-layout practices. Source: https://www.ti.com/product/DRV8871
- TI CAN physical-layer application report SLLA270: CAN uses a multipoint bus with twisted pair, termination at both ends, and attention to stub length and propagation delay. This supports using a real CAN transceiver, a 120 ohm termination option, short stubs, and test points. Source: https://www.ti.com/lit/an/slla270/slla270.pdf
- TI TCAN332 product page: a 3.3 V CAN transceiver is attractive because it avoids a 5 V logic interface between the STM32 and transceiver. Source: https://www.ti.com/product/TCAN332
- Microchip TC4427A product page: a simple dual MOSFET gate driver can drive a MOSFET gate harder than an STM32 pin and is easier to reason about than a full H-bridge driver. Source: https://www.microchip.com/en-us/product/TC4427A
- ST LIS3DH product page: a simple 3-axis digital accelerometer with I2C/SPI output is a reasonable later vibration sensor. For Version 1, a header for an accelerometer module is enough. Source: https://www.st.com/en/mems-and-sensors/lis3dh.html
- KiCad schematic documentation: KiCad supports labels, net classes, ERC, and forward annotation from schematic to PCB. This supports keeping schematic sections readable and assigning power nets intentionally. Source: https://docs.kicad.org/9.0/en/eeschema/eeschema.html
- Analog Devices LTspice page: LTspice is appropriate for early transient checks of the motor switch, flyback path, RC filters, and voltage divider behavior. Source: https://www.analog.com/en/resources/design-tools-and-calculators/ltspice-simulator.html

## Engineering Community Patterns Reviewed

Across manufacturer forums, KiCad discussions, PCB review discussions, and student project advice, recurring advice was:

- Make the first hardware revision small enough to finish and test.
- Show documentation, requirements, schematics, PCB decisions, firmware structure, and measured results.
- Do not pretend a simulation is a lab result.
- Add test points early.
- Separate noisy motor current loops from MCU analog measurements.
- Use a current-limited bench supply for first power-up.
- Use known-good dev boards and breakout modules before designing every subsystem from scratch.
- Recruiters tend to value projects that show tradeoffs, debugging evidence, and validation more than projects with many untested features.

## Common Beginner Mistakes To Avoid

- Choosing a motor whose stall current is far above the power stage rating.
- Reading only MOSFET threshold voltage and assuming the MOSFET is fully on.
- Forgetting a flyback path for an inductive motor.
- Routing motor current through the same thin ground path used by ADC measurements.
- Measuring current without considering shunt power dissipation.
- Adding bidirectional control before one-direction control is reliable.
- Designing a custom switching regulator before the main motor-control behavior is proven.
- Adding CAN before defining timeout and safe-state behavior.
- Presenting simulated waveforms as measured hardware data.

## Version 1 Research Conclusion

The best first version is a one-direction, low-side MOSFET motor controller using an STM32 Nucleo board and simple sensors. It gives strong internship value because it includes real power switching, embedded control, ADC sensing, fault handling, CAN, schematic capture, simulation, and eventual PCB layout, while staying buildable for a first-year student.

## Version 1 Part Selection Update

The motor was narrowed to Pololu item 3039, a 50:1 Micro Metal Gearmotor HPCB 12V. The important manufacturer data points are 12 V rated voltage, 80 mA no-load current, and 0.75 A extrapolated stall current. Pololu also warns that stall values are theoretical and that stalling can damage the motor or gearbox. Source: https://www.pololu.com/product/3039

The larger DFRobot 12 V encoder gearmotor class was not selected for Version 1 because published product data shows stall currents in the several-amp range. That would force a higher-current first build and move the project away from the requested low-cost, simple 1 A to 2 A bench target.

Final Version 1 critical parts selected from manufacturer documentation:

- Infineon IRLZ44NPBF MOSFET
- Microchip TC4427ACPA MOSFET driver
- Diodes Incorporated 1N5822 Schottky flyback diode
- Texas Instruments INA180A1IDBVR current-sense amplifier
- Texas Instruments TCAN332DR CAN transceiver
- Littelfuse RXEF110 resettable PTC
- Littelfuse SMBJ18A TVS diode
