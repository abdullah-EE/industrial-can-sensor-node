# LTspice Simulations

These files are starter simulations for Version 1 of the 12 V brushed DC motor controller.

Current files:

- `v1_low_side_motor_switch.cir` - low-side MOSFET motor switch with flyback diode and shunt resistor
- `v1_current_sense_filter.cir` - shunt plus current-sense gain and ADC RC filter
- `v1_voltage_divider_filter.cir` - 12 V rail divider and ADC RC filter

Rules:

- Do not treat simulated results as measured hardware performance.
- Replace generic device models with manufacturer models when the exact MOSFET, diode, and amplifier are selected.
- Record any plotted waveforms or measurements in a separate simulation note before comparing to hardware.
