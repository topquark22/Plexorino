# Plexorino/mux16

16-line multiplexer for input to Arduino.

Uncomment `#define MUX16` in `plexorino.h`.

## 74LS150 pinout and wiring

- **En**: Input signal n
- custom: Per your use case. Include external pullup resistors if required.

| pin | description |  wire to | 
|-----|-------------|---------|
| 1   | E7 input | custom |
| 2   | E6 input | custom |
| 3   | E5 input | custom |
| 4   | E4 input | custom |
| 5   | E3 input | custom |
| 6   | E2 input | custom |
| 7   | E1 input | custom |
| 8   | E0 input | custom |
| 9   | STROBE | GND \[1\] |
| 10 | multiplexed signal (inverted) | Arduino A0 |
| 11 | address bus 3 | Arduino A1 |
| 12 | Vss | GND |
| 13 | address bus 2 | Arduino D4 |
| 14 | address bus 1 | Arduino D3 |
| 15 | address bus 0 | Arduino D2 |
| 16 | E15 input | custom |
| 17 | E14 input | custom | 
| 18 | E13 input | custom | 
| 19 | E12 input | custom | 
| 20 | E11 input | custom |
| 21 | E10 input | custom |
| 22 | E9 input  | custom |
| 23 | E8 input | custom |
| 24 | Vdd | +5V |

 \[1\] You can implement STROBE in your circuit, but the stock Plexorino does not use it.

 ## Testing

Leave `#define TEST_CODE` uncommented. You will see output giving the logic level of each pin at 1-second intervals.
