# ERC Notes

## 2026-07-12 KiCad ERC

Command run:

```powershell
& 'C:\Program Files\KiCad\10.0\bin\kicad-cli.exe' sch erc --output .tmp_erc.rpt kicad\kicad.kicad_sch
```

Saved report:

- `hardware/kicad/erc_2026-07-12-current.rpt`

Result:

- ERC completed.
- KiCad reported 43 total violations: 4 errors and 39 warnings.
- The schematic exports a netlist.
- No literal `??` unresolved-symbol markers remain in `kicad/kicad.kicad_sch`.
- The project-local symbol library `kicad/v1_symbols.kicad_sym` loads with `kicad-cli sym export svg`.

Remaining errors:

- D2 pin 2 at `(60.96 mm, 30.48 mm)` is reported unconnected.
- D2 pin 1 at `(60.96 mm, 40.64 mm)` is reported unconnected.
- C1 pin 2 at `(78.74 mm, 30.48 mm)` is reported unconnected.
- C1 pin 1 at `(78.74 mm, 40.64 mm)` is reported unconnected.

Interpretation:

- These are genuine schematic cleanup blockers in the input-protection area.
- The wires and junctions were placed at the reported coordinates, but KiCad still reports the custom vertical TVS/capacitor pins as unconnected. The next pass should replace these temporary project-local vertical symbols with standard KiCad library symbols or redraw the embedded pin geometry in the KiCad GUI.

Remaining warnings:

- 4 footprint library warnings for terminal-block/fuse symbols.
- 1 label-multiple-wires warning on `PWM_GATE`.
- 1 isolated label warning on `TEMP_ADC`.
- 33 unconnected wire endpoint warnings from the current hand-authored schematic geometry.

Next KiCad task:

Open the schematic in KiCad GUI, replace the temporary project-local passives with standard library symbols where possible, snap the remaining wires and labels to pins, verify the power and motor-current paths visually, then rerun ERC until there are zero genuine electrical errors.
