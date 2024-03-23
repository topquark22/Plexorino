# Plexorino/mux16

16-line multiplexer for input to Arduino.

Uncomment `#define MUX16` in `plexorino.h`.

## 74LS150 pinout and wiring

- **En**: Input signal n. Include external pullup resistors if required.
- custom: Per your use case.

| pin | description |  wire to | 
|-----|-------------|---------|
| 1   | input E7 | custom |
| 2   | input E6 | custom |
| 3   | input E5 | custom |
| 4   | input E4 | custom |
| 5   | input E3 | custom |
| 6   | input E2 | custom |
| 7   | input E1 | custom |
| 8   | input E0 | custom |
| 9   | input STROBE | GND \[1\] |
| 10 | multiplexed signal (inverted) | Arduino A0 |
| 11 | address bus 3 | Arduino A1 |
| 12 | Vss | GND |
| 13 | address bus 2 | Arduino D4 |
| 14 | address bus 1 | Arduino D3 |
| 15 | address bus 0 | Arduino D2 |
| 16 | input E15 | custom |
| 17 | input E14 | custom | 
| 18 | input E13 | custom | 
| 19 | input E12 | custom | 
| 20 | input E11 | custom |
| 21 | input E10 | custom |
| 22 | input E9  | custom |
| 23 | input E8  | custom |
| 24 | Vdd | +5V |

 \[1\] You can implement STROBE in your circuit, but the stock Plexorino does not use it.

 ## Testing

Leave `#define TEST_CODE` uncommented. You will see output giving the logic level of each pin at 1-second intervals.
