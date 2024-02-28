# Plexorino/mux16

16-line multiplexer for input to Arduino.

## 74LS150 pinout

**E\***: input signals

| pin | function | wire to |
|-----|----------|---------|
| 1   | E7  | custom |
| 2   | E6  | custom |
| 3   | E5  | custom |
| 4   | E4  | custom |
| 5   | E3  | custom |
| 6   | E2  | custom |
| 7   | E1  | custom |
| 8   | E0  | custom |
| 9   | strobe | GND \[1\] |
| 10 | multiplexed signal (inverted) | A0 |
| 11 | addr 8's bit | A1 |
| 12 | Vss | GND |
| 13 | addr 4's bit | D4 |
| 14 | addr 2's bit | D3 |
| 15 | addr 1's bit | D2 |
| 16 | E15 | custom |
| 17 | E14 | custom | 
| 18 | E13 | custom | 
| 19 | E12 | custom | 
| 20 | E11 | custom |
| 21 | E10 | custom |
| 22 | E9  | custom |
| 23 | E8 | custom |
| 24 | Vdd | +5V |

 \[1\] You can implement STROBE in your circuit, but this sketch does not use it.
