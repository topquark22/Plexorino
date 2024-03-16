# Plexorino/mux16

16-line multiplexer for input to Arduino.

## 74LS150 pinout and wiring

- **En**: Input signal at address n
- custom: Per your use case. Include external pullup resistors if required.

| pin | function |  wire to | 
|-----|----------|---------|
| 1   | E7  | custom |
| 2   | E6  | custom |
| 3   | E5  | custom |
| 4   | E4  | custom |
| 5   | E3  | custom |
| 6   | E2  | custom |
| 7   | E1  | custom |
| 8   | E0  | custom |
| 9   | STROBE | GND \[1\] |
| 10 | multiplexed signal (inverted) | A0 |
| 11 | address bus 3 | A1 |
| 12 | Vss | GND |
| 13 | address bus 2 | D4 |
| 14 | address bus 1 | D3 |
| 15 | address bus 0 | D2 |
| 16 | E15 | custom |
| 17 | E14 | custom | 
| 18 | E13 | custom | 
| 19 | E12 | custom | 
| 20 | E11 | custom |
| 21 | E10 | custom |
| 22 | E9  | custom |
| 23 | E8 | custom |
| 24 | Vdd | +5V |

 \[1\] You can implement STROBE in your circuit, but the stock Plexorino does not use it.

 ## Testing

Leave `#define TEST_CODE` uncommented. You will see output giving the logic level of each pin at 1-second intervals.
