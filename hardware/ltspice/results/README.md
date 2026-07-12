# LTspice Results

## 2026-07-12

LTspice executable located:

- `C:\Users\hayda\AppData\Local\Programs\ADI\LTspice\LTspice.exe`

Batch simulations attempted:

```powershell
& 'C:\Users\hayda\AppData\Local\Programs\ADI\LTspice\LTspice.exe' -b hardware\ltspice\v1_low_side_motor_switch.cir
& 'C:\Users\hayda\AppData\Local\Programs\ADI\LTspice\LTspice.exe' -b hardware\ltspice\v1_current_sense_filter.cir
& 'C:\Users\hayda\AppData\Local\Programs\ADI\LTspice\LTspice.exe' -b hardware\ltspice\v1_voltage_divider_filter.cir
```

Result:

- Each command returned exit code 0.
- No `.raw`, `.log`, `.plt`, `.csv`, or waveform export files were produced in the repository.
- Therefore no actual waveform evidence is available yet.

Current runnable decks:

- `../v1_low_side_motor_switch.cir`
- `../v1_current_sense_filter.cir`
- `../v1_voltage_divider_filter.cir`

Do not present expected values from the `.cir` files as measured or simulated waveform results. The next LTspice task is to run the decks interactively or fix the batch-output path, then save actual exported waveform data under this directory.
