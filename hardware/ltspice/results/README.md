# LTspice Results

## 2026-07-12

LTspice executable used:

- `C:\Users\hayda\AppData\Local\Programs\ADI\LTspice\LTspice.exe`

Command pattern used from `hardware/ltspice`:

```powershell
& 'C:\Users\hayda\AppData\Local\Programs\ADI\LTspice\LTspice.exe' -b -ascii <deck>.cir
```

Actual exported waveform evidence:

- `motor_switch_voltage_current_flyback.csv`
  - source deck: `../v1_low_side_motor_switch.cir`
  - exported columns: `time`, `V(sw)`, `I(Rmotor)`, `I(Dfly)`
- `current_sense_output.csv`
  - source deck: `../v1_current_sense_filter.cir`
  - exported columns: `time`, `V(isense_adc)`, `V(isense_raw)`, `V(shunt_node)`
- `supply_divider_output.csv`
  - source deck: `../v1_voltage_divider_filter.cir`
  - exported columns: `time`, `V(vin_12v)`, `V(vsense_adc)`, `V(vsense_raw)`

Simulation summaries from LTspice logs:

- Low-side motor switch:
  - average motor current from 5 ms to 10 ms: `0.293581739608 A`
  - peak motor current from 0 ms to 10 ms: `0.355529999072 A`
  - peak switch-node voltage from 0 ms to 10 ms: `12.5527299537 V`
- Current-sense filter:
  - max `V(ISENSE_ADC)`: `2.5 V`
- Supply divider:
  - `V(VSENSE_ADC)` at 12 V input: `2.51527700834 V`
  - `V(VSENSE_ADC)` at 9 V input: `1.95537249829 V`
  - `V(VSENSE_ADC)` at 15 V input: `3.1765692121 V`

These are simulation results only. They are not measured hardware validation.
