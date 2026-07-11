# Design Calculations

## Selected Motor

Motor: Pololu item 3039, 50:1 Micro Metal Gearmotor HPCB 12V.

Manufacturer data used:

- Rated voltage: 12 V
- No-load speed: 650 RPM
- No-load current: 80 mA
- Extrapolated stall torque: 0.67 kg.cm
- Extrapolated stall current: 0.75 A
- Manufacturer warning: stall values are theoretical and stalling can damage the motor/gearbox.
- Manufacturer operating guidance: keep brushed DC motor operation at 25 percent or less of stall current when possible.

Source: https://www.pololu.com/product/3039

Important interpretation: Pololu does not list a separate rated load current for item 3039. The design therefore uses the listed 80 mA no-load current, 0.75 A extrapolated stall current, and Pololu's 25 percent of stall-current guidance for the first continuous operating target.

## Motor Current Targets

Continuous learning target:

```text
I_cont_target = 0.25 * I_stall
I_cont_target = 0.25 * 0.75 A
I_cont_target = 0.1875 A
```

Firmware warning threshold:

```text
I_warn = 0.75 A
```

Firmware shutdown threshold:

```text
I_shutdown = 1.20 A
```

Why the shutdown threshold is above stall current: the measured current can briefly spike during startup and PWM edges. The firmware threshold should catch abnormal sustained current without nuisance-tripping instantly. First tests still use a bench supply current limit below or near 1 A.

## Motor Winding Approximation For Simulation

At stall, back-EMF is zero, so the winding resistance can be estimated from Ohm's law:

```text
R_motor = V_motor / I_stall
R_motor = 12 V / 0.75 A
R_motor = 16 ohm
```

LTspice uses `RMOTOR = 16` as a first approximation. Motor inductance is not specified by the motor product page, so `LMOTOR = 1 mH` remains an assumption for transient exploration only.

## MOSFET Selection

Selected MOSFET: Infineon IRLZ44NPBF.

Datasheet/library headline values used:

- N-channel logic-level MOSFET
- Drain-source voltage rating: 55 V
- TO-220 package
- Very large current margin compared with the 0.75 A motor stall current

Voltage margin:

```text
VDS_rating / V_motor = 55 V / 12 V = 4.58x
```

Conduction loss estimate using a conservative `RDS(on) = 0.035 ohm` at logic-level gate drive:

```text
P_Q_stall = I_stall^2 * RDS(on)
P_Q_stall = 0.75^2 * 0.035
P_Q_stall = 0.0197 W

P_Q_shutdown = I_shutdown^2 * RDS(on)
P_Q_shutdown = 1.20^2 * 0.035
P_Q_shutdown = 0.0504 W
```

Beginner meaning: the MOSFET should barely warm up in this Version 1 current range. The bigger risk is wiring/layout mistakes, not MOSFET heat.

## Gate Drive

Selected gate driver: Microchip TC4427ACPA.

Datasheet values used:

- Supply range: 4.5 V to 18 V
- Non-inverting dual MOSFET driver
- Logic high input threshold compatible with STM32 3.3 V output
- Peak output current: 1.5 A

Design choice:

- Power the TC4427A from the Nucleo 5 V rail.
- Drive its input from STM32 PWM.
- Add a 22 ohm series gate resistor.
- Add a 100 k gate pulldown so the MOSFET stays off during reset.
- Ground the unused driver input.

Approximate peak gate-resistor-limited current:

```text
I_gate_initial ~= V_driver / R_gate
I_gate_initial ~= 5 V / 22 ohm
I_gate_initial ~= 0.227 A
```

The driver can supply more than this, so the resistor mainly softens edges and reduces ringing.

## Flyback Diode

Selected diode: Diodes Incorporated 1N5822.

Manufacturer data used:

- Average rectified current: 3 A
- Repetitive reverse voltage: 40 V
- Schottky diode in DO-201AD package

Current margin:

```text
I_diode_rating / I_stall = 3 A / 0.75 A = 4x
```

Voltage margin:

```text
V_RRM / V_motor = 40 V / 12 V = 3.33x
```

The diode is connected from `MOTOR_SW` to `VMOTOR_12V`, with cathode at `VMOTOR_12V` and anode at `MOTOR_SW`.

## Shunt And Current Sense

Selected shunt: 0.05 ohm current-sense resistor.

Selected amplifier: INA180A1, gain 20 V/V.

Current-to-voltage equation:

```text
V_shunt = I_motor * R_shunt
V_isense = V_shunt * Gain
V_isense = I_motor * 0.05 ohm * 20
V_isense = I_motor * 1.0 V/A
```

At no-load current:

```text
V_isense = 0.08 A * 1.0 V/A = 0.08 V
ADC_counts = 0.08 / 3.3 * 4095 = 99 counts
```

At stall current:

```text
V_isense = 0.75 A * 1.0 V/A = 0.75 V
ADC_counts = 0.75 / 3.3 * 4095 = 931 counts
```

At firmware shutdown current:

```text
V_isense = 1.20 A * 1.0 V/A = 1.20 V
ADC_counts = 1.20 / 3.3 * 4095 = 1489 counts
```

ADC full-scale current:

```text
I_full_scale = 3.3 V / 1.0 V/A = 3.3 A
```

Shunt power:

```text
P_shunt_stall = 0.75^2 * 0.05 = 0.028 W
P_shunt_shutdown = 1.20^2 * 0.05 = 0.072 W
P_shunt_3A = 3.0^2 * 0.05 = 0.45 W
```

A 1 W or 2 W 2512 shunt has comfortable margin.

## Supply Voltage Divider

Selected divider:

- Top resistor: 100 k
- Bottom resistor: 27 k
- ADC filter resistor: 1 k
- ADC filter capacitor: 47 nF

Divider ratio:

```text
Ratio = R_bottom / (R_top + R_bottom)
Ratio = 27000 / (100000 + 27000)
Ratio = 0.2126
```

ADC voltage at nominal supply:

```text
V_adc_12V = 12 V * 0.2126 = 2.55 V
ADC_counts_12V = 2.55 / 3.3 * 4095 = 3165 counts
```

ADC voltage at 15 V:

```text
V_adc_15V = 15 V * 0.2126 = 3.19 V
ADC_counts_15V = 3.19 / 3.3 * 4095 = 3958 counts
```

Approximate divider current at 12 V:

```text
I_divider = 12 V / 127 k = 94.5 uA
```

Divider resistor power:

```text
P_top = I^2 * 100 k = 0.000893 W
P_bottom = I^2 * 27 k = 0.000241 W
```

0805 resistors are more than sufficient.

ADC filter cutoff:

```text
f_c = 1 / (2*pi*R*C)
f_c = 1 / (2*pi*1000*47 nF)
f_c = 3386 Hz
```

This is fast enough for supply monitoring and slow enough to reduce PWM noise.

## PTC Fuse

Selected PTC: Littelfuse RXEF110.

Design intent:

- Hold current: 1.10 A
- Trip current: 2.20 A

Why this part:

- The selected motor has 0.75 A extrapolated stall current.
- The PTC should not trip instantly during normal startup or brief stall tests.
- Sustained wiring faults or incorrect larger motors should push it toward trip.

The PTC is not the only protection. Firmware overcurrent shutdown and bench supply current limiting are still required.

## TVS Diode

Selected TVS: Littelfuse SMBJ18A.

Design intent:

- 18 V reverse standoff is above normal 12 V operation.
- The 55 V MOSFET has margin above the TVS clamp region.
- The TVS is a protection footprint, not permission to hot-plug or abuse the board.

## Thermal Summary

At the selected motor's 0.75 A extrapolated stall current:

```text
P_shunt = 0.028 W
P_mosfet ~= 0.020 W
P_flyback is pulsed and depends on PWM duty and motor current decay
```

These losses are small. Thermal testing is still required because wiring, diode placement, board copper, and motor loading affect real temperatures.

## Final Version 1 Limits

- Nominal supply: 12 V
- Intended continuous motor current: about 0.19 A or less until measured
- Motor stall current from manufacturer: 0.75 A extrapolated
- Firmware overcurrent shutdown: 1.20 A
- ADC current full scale: about 3.3 A
- Bench supply current limit for first test: 0.5 A to 1.0 A
