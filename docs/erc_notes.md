# ERC Notes

## 2026-07-12 KiCad ERC

Command run:

```powershell
& 'C:\Program Files\KiCad\10.0\bin\kicad-cli.exe' sch erc --output .tmp_erc.rpt kicad\kicad.kicad_sch
```

Saved report:

- `hardware/kicad/erc_2026-07-12.rpt`

Result:

- ERC completed.
- KiCad reported 165 total violations: 63 errors and 102 warnings.

Important interpretation:

- The schematic file loads in KiCad and exports a netlist.
- The schematic is not ERC-clean.
- Most errors are dangling global labels and off-grid wire endpoints caused by the first hand-written symbol placement pass.
- These are genuine schematic cleanup issues, not justified electrical warnings.

Justified warnings:

- Several footprint warnings are expected at this stage because exact footprint library mappings for the terminal blocks, PTC fuse, and thermistor need to be checked before layout.
- The PCB has not been routed, so footprint cleanup remains a pre-layout task.

Unjustified errors that must be fixed next:

- Dangling labels on power, motor, ADC, CAN, and Nucleo interface nets.
- Off-grid wire endpoints.
- A few multiple-net-name warnings caused by the temporary label/wire placement pass.

Next KiCad task:

Open the schematic in KiCad GUI, snap all symbols and labels to the active connection grid, replace temporary label stubs with normal wires/net labels, add/import any missing footprints, and rerun ERC until only documented footprint or intentional warnings remain.
